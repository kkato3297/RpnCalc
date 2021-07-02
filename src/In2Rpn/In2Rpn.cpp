#include <In2Rpn/In2Rpn.h>
#include <Utility.h>
#include <vector>
#include <map>
#include <regex>
#include <algorithm>

#include <iostream>

const map<string, int> operatorOrder = {
	{ "+",			0			},
	{ "-",			0			},
	{ "*",			1			},
	{ "/",			1			},
	{ "^",			2			},
	{ "square",		2			},
	{ "cube",		2			},
	{ "inverse",	2			},
	{ "%",			2			},
	{ "!",			1			},
	{ "abs",		0x7fffffff	},
	{ "sin",		0x7fffffff	},
	{ "cos",		0x7fffffff	},
	{ "tan",		0x7fffffff	},
	{ "sinh",		0x7fffffff	},
	{ "cosh",		0x7fffffff	},
	{ "tanh",		0x7fffffff	},
	{ "asin",		0x7fffffff	},
	{ "acos",		0x7fffffff	},
	{ "atan",		0x7fffffff	},
	{ "asinh",		0x7fffffff	},
	{ "acosh",		0x7fffffff	},
	{ "atanh",		0x7fffffff	},
	{ "LCM",		0x7fffffff	},
	{ "GCD",		0x7fffffff	},
	{ "sqrt",		0x7fffffff	},
	{ "cbrt",		0x7fffffff	},
	{ "Rand",		0x7fffffff	},
	{ "iRand",		0x7fffffff	},
};

map<string, int> functionOrder = {
	{ "sin", 		0x7fffffff	},
	{ "cos", 		0x7fffffff	},
	{ "tan", 		0x7fffffff	},
};

map<string, int> constList = {
	{ "M_PI",		0			},
	{ "M_E",		0			},
};

map<string, int> memoryList = {
	{ "MEMORY_M",	0			},
	{ "MEMORY_A",	0			},
	{ "MEMORY_B",	0			},
	{ "MEMORY_C",	0			},
	{ "MEMORY_D",	0			},
	{ "MEMORY_X",	0			},
	{ "MEMORY_Y",	0			},
	{ "MEMORY_ANS",	0			},
};

bool isNumeric(string &token)
{
	bool bRet = false;

	try {
		stod(token);
		bRet = true;
	}
	catch (std::invalid_argument &e) {
		bRet = constList.find(token) != constList.end() || memoryList.find(token) != memoryList.end();
	};

	if (token == ".") {
		bRet = true;
	}

	return bRet;
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

In2Rpn::In2Rpn(const string &expr)
{
	string work;
	vector<string> tokenList = {};

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
		tokenList.push_back(iter->str());
	}

	Parser parser;
	m_tokenTree = parser.parse(tokenList);
}

In2Rpn::~In2Rpn(void)
{}

string In2Rpn::toRpn(void)
{
	return m_tokenTree.getRootNode()->toString();
}

string In2Rpn::toSolutionExpression(void)
{
	return m_tokenTree.getRootNode()->toSolutionString();
}

string In2Rpn::separateToken(const string &expr)
{
	string work = expr;

#if 1
	{
		vector<string> tokenlist;
		for (auto &key : operatorOrder) {
			tokenlist.push_back(escape(key.first));
		}
        for (auto &key : constList) {
            tokenlist.push_back(escape(key.first));
        }
        for (auto &key : memoryList) {
            tokenlist.push_back(escape(key.first));
        }
		tokenlist.push_back(escape("("));
		tokenlist.push_back(escape(")"));
		tokenlist.push_back(escape(","));
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
