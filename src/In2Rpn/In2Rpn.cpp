#include <In2Rpn/In2Rpn.h>
#include <Stack.h>
#include <map>
#include <regex>
#include <algorithm>

#include <iostream>

const map<string, int> operatorOrder = {
	{ "+",		0			},
	{ "-",		0			},
	{ "*",		1			},
	{ "/",		1			},
	{ "abs",	0x7fffffff	},
	{ "sin",	0x7fffffff	},
	{ "cos",	0x7fffffff	},
	{ "tan",	0x7fffffff	},
	{ "sinh",	0x7fffffff	},
	{ "cosh",	0x7fffffff	},
	{ "tanh",	0x7fffffff	},
	{ "asin",	0x7fffffff	},
	{ "acos",	0x7fffffff	},
	{ "atan",	0x7fffffff	},
	{ "asinh",	0x7fffffff	},
	{ "acosh",	0x7fffffff	},
	{ "atanh",	0x7fffffff	},
};

map<string, int> functionOrder = {
	{ "sin", 0x7fffffff },
	{ "cos", 0x7fffffff },
	{ "tan", 0x7fffffff },
};

bool isNumeric(string &token)
{
	bool bRet = false;

	try {
		stod(token);
		bRet = true;
	}
	catch (std::invalid_argument &e) {
		bRet = false;
	};

	return bRet;
}

string join(vector<string> &list, const string &spliter)
{
	string buffer = "";

	for (auto iter = list.begin(); iter < list.end(); iter++) {
		buffer += (*iter);

		if (iter < list.end() - 1) {
			buffer += spliter;
		}
	}

	return buffer;
}

double strtod(const string::iterator begin, string::iterator &end)
{
	double result;
	char *pEnd = nullptr;

	result = strtod(&begin[0], &pEnd);
	end = begin + (pEnd - &begin[0]);

	return result;
}

string escape(const string &str)
{
	regex re(R"(.*([\\,\*,\+,\.,\?,\{,\},\(,\),\[,\],\^,\$,\|]))");

	return regex_replace(str, re, "\\$1");
}

In2Rpn::In2Rpn(string &expr)
{
	string work;

#if 1
	work = separateToken(expr);
#else
	work = expr;
#endif

	cout << __FILE__ << "(" << __LINE__ << "): expr: \"" << work << "\"" << endl;

	regex re(R"((?:([^\s]+))+)");
	sregex_iterator iter(work.cbegin(), work.cend(), re);
	sregex_iterator end;

	for (; iter != end; iter++) {
		m_tokenList.push_back(iter->str());
	}
}

In2Rpn::~In2Rpn(void)
{}

string In2Rpn::toRpn(void)
{
	Stack<string> stack;
	vector<string> buffer;

	for (auto &token : m_tokenList) {
		if (isNumeric(token)) {
			// それは数字か
			buffer.push_back(token);
		} else if (token == ")") {
			// 右かっこか
			string temp = stack.pop();
			while (temp != "(") {
				buffer.push_back(temp);

				temp = stack.pop();
			}
		} else if (token == "(") {
			// 左かっこか
			stack.push(token);
		} else {
			// スタックは空か
			while (stack.length()) {
				string temp = stack.back();
				// スタックの最上位演算子よりトークン演算子の優先順序が低い
				if (operatorOrder.find(temp) != operatorOrder.end() &&
					operatorOrder.at(temp) >= operatorOrder.at(token)) {
					// スタックからポップし、それをバッファへ
					buffer.push_back(stack.pop());
				} else {
					break;
				}
			}

			stack.push(token);
		}
	}

	while (stack.length()) {
		buffer.push_back(stack.pop());
	}

	return join(buffer, " ");
}

string In2Rpn::separateToken(string &expr)
{
	string work = expr;

#if 1
	{
		vector<string> tokenlist;
		for (auto &key : operatorOrder) {
			tokenlist.push_back(escape(key.first));
		}
		tokenlist.push_back(escape("("));
		tokenlist.push_back(escape(")"));
		sort(tokenlist.begin(), tokenlist.end(), [](const string &a, const string &b) {
			return a.size() > b.size();
		});
		regex re(R"(()" + join(tokenlist, "|") + R"((?:\s?)+))");

		work = regex_replace(work, re, "$1 ");
	}
#else
	for (auto &key : operatorOrder) {
		regex re(R"(()" + escape(key.first) + R"((?:\s?)+))");

		work = regex_replace(work, re, "$1 ");
	}
	for (auto &key : {string("("), string(")")}) {
		regex re(R"(()" + escape(key) + R"((?:\s?)+))");

		work = regex_replace(work, re, "$1 ");
	}
#endif
	for (auto iter = work.begin(); iter < work.end();) {
		string::iterator end;

		strtod(iter, end);

		if (iter == end) {
			iter++;
			continue;
		}

		if (end < work.end()) {
			ptrdiff_t diff = end - work.begin();
			work.insert(end, ' ');
			end = work.begin() + diff + 1;
		}

		if (end <= work.end()) {
			iter = end;
		}
	}
	{
		// 式の先頭および終端に存在するスペースを削除
		regex re(R"(^(?:[\s]+)?([^\s].+[^\s])(?:[\s]+)?$)");

		work = regex_replace(work, re, "$1");
	}
	{
		// トークン間の余計なスペースを削除
		regex re(R"(([^\s]+)(?:[\s]+))");

		work = regex_replace(work, re, "$1 ");
	}

	return work;
}