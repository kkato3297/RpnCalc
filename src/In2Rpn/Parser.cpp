//
// Created by KK Systems on 2020-01-27.
//

#include <In2Rpn/Parser.h>
#include <Exception.h>
#include <map>

std::string join(const std::vector<std::string>& v, const char* delim = 0)
{
	std::string s;

	if (!v.empty()) {
		s += v[0];
		for (decltype(v.size()) i = 1, c = v.size(); i < c; ++i) {
			if (delim) s += delim;
			s += v[i];
		}
	}
	return s;
}

IExpressionNode::IExpressionNode(void)
{
}

IExpressionNode::~IExpressionNode(void)
{
}

class UnaryExpressionNode: public IExpressionNode
{
public:
	UnaryExpressionNode(void);
	~UnaryExpressionNode(void);

	void setRhs(shared_ptr<IExpressionNode>& rhs);
	void setRhs(shared_ptr<IExpressionNode>&& rhs);
	shared_ptr<IExpressionNode>& getRhs(void);

	void setOperator(string& ope);
	void setOperator(string&& ope);
	string& getOperator(void);

	string toString(void);
	string toSolutionString(void);

private:
	shared_ptr<IExpressionNode> m_rhs;
	string                      m_operator;
};

UnaryExpressionNode::UnaryExpressionNode(void)
: m_rhs(nullptr), m_operator("")
{
}

UnaryExpressionNode::~UnaryExpressionNode(void)
{
}

void UnaryExpressionNode::setRhs(shared_ptr<IExpressionNode>& rhs)
{
	m_rhs = rhs;
}

void UnaryExpressionNode::setRhs(shared_ptr<IExpressionNode>&& rhs)
{
	shared_ptr<IExpressionNode>& node = rhs;
	setRhs(rhs);
}

shared_ptr<IExpressionNode>& UnaryExpressionNode::getRhs(void)
{
	return m_rhs;
}

void UnaryExpressionNode::setOperator(string& ope)
{
	m_operator = ope;
}

void UnaryExpressionNode::setOperator(string&& ope)
{
	m_operator = ope;
}

string& UnaryExpressionNode::getOperator(void)
{
	return m_operator;
}

string UnaryExpressionNode::toString()
{
	string result = m_rhs->toString();

	if (m_operator != "") {
		result += " " + m_operator;
	}

	return result;
}

string UnaryExpressionNode::toSolutionString()
{
	string result = "( ";

	if (m_operator == "+" || m_operator == "-" || m_operator == "~") {
		result += m_operator + " ";
	}

	result += m_rhs->toSolutionString();

	if (m_operator == "!" || m_operator == "square" ||
		m_operator == "cube" || m_operator == "inverse" ||
		m_operator == "%") {
		result += " " + m_operator;
	}

	result += " )";

	return result;
}

class NumberExpressionNode: public IExpressionNode
{
public:
	NumberExpressionNode(void);
	~NumberExpressionNode(void);

	void setNumber(const string& num);
	void setNumber(const string&& num);
	string& getNumber(void);

	string toString(void);
	string toSolutionString(void);

private:
	string m_value;
};

NumberExpressionNode::NumberExpressionNode(void)
: m_value("")
{
}

NumberExpressionNode::~NumberExpressionNode(void)
{
}

void NumberExpressionNode::setNumber(const string& num)
{
	m_value = num;
}

void NumberExpressionNode::setNumber(const string&& num)
{
	m_value = num;
}

string& NumberExpressionNode::getNumber(void)
{
	return m_value;
}

string NumberExpressionNode::toString()
{
	return m_value;
}

string NumberExpressionNode::toSolutionString()
{
	return m_value;
}

class FunctionExpressionNode: public IExpressionNode
{
public:
	FunctionExpressionNode(void);
	~FunctionExpressionNode(void);

	void setFunction(const string& function);
	void setFunction(const string&& function);
	string& getFunction(void);
	void setArgument(const vector<shared_ptr<IExpressionNode>>& argument);
	void setArgument(const vector<shared_ptr<IExpressionNode>>&& argument);
	vector<shared_ptr<IExpressionNode>>& getArgument(void);

	string toString(void);
	string toSolutionString(void);

private:
	string								m_function;
	vector<shared_ptr<IExpressionNode>>	m_argument;
};

FunctionExpressionNode::FunctionExpressionNode(void)
: m_function(""), m_argument()
{
}

FunctionExpressionNode::~FunctionExpressionNode(void)
{
}

void FunctionExpressionNode::setFunction(const string& function)
{
	m_function = function;
}

void FunctionExpressionNode::setFunction(const string&& function)
{
	m_function = function;
}

string& FunctionExpressionNode::getFunction(void)
{
	return m_function;
}

void FunctionExpressionNode::setArgument(const vector<shared_ptr<IExpressionNode>>& argument)
{
	m_argument = argument;
}

void FunctionExpressionNode::setArgument(const vector<shared_ptr<IExpressionNode>>&& argument)
{
	m_argument = argument;
}

vector<shared_ptr<IExpressionNode>>& FunctionExpressionNode::getArgument(void)
{
	return m_argument;
}

string FunctionExpressionNode::toString()
{
	string result = "";

	for (auto argument : m_argument) {
		result += argument->toString() + " ";
	}

	result += m_function + "@" + to_string(m_argument.size());
	return result;
}

string FunctionExpressionNode::toSolutionString()
{
	string result = "( " + m_function + "( ";
	vector<string> argumentList = {};

	std::transform(m_argument.begin(), m_argument.end(), std::inserter(argumentList, argumentList.end()), [](const auto& argument) {
		return argument->toSolutionString();
	});
	result += join(argumentList, ", ");

	result += " ) )";

	return result;
}

class IdentiferExpressionNode: public IExpressionNode
{
public:
	IdentiferExpressionNode(void);
	~IdentiferExpressionNode(void);

	void setIdentifer(const string& num);
	void setIdentifer(const string&& num);
	string& getIdentifer(void);

	string toString(void);
	string toSolutionString(void);

private:
	string m_ident;
};

IdentiferExpressionNode::IdentiferExpressionNode(void)
: m_ident("")
{
}

IdentiferExpressionNode::~IdentiferExpressionNode(void)
{
}

void IdentiferExpressionNode::setIdentifer(const string& ident)
{
	m_ident = ident;
}

void IdentiferExpressionNode::setIdentifer(const string&& ident)
{
	m_ident = ident;
}

string& IdentiferExpressionNode::getIdentifer(void)
{
	return m_ident;
}

string IdentiferExpressionNode::toString()
{
	return m_ident;
}

string IdentiferExpressionNode::toSolutionString()
{
	return m_ident;
}

class TermExpressionNode: public IExpressionNode
{
public:
	TermExpressionNode(void);
	~TermExpressionNode(void);

	void setLhs(shared_ptr<IExpressionNode>& lhs);
	void setLhs(shared_ptr<IExpressionNode>&& lhs);
	void setRhs(shared_ptr<IExpressionNode>& rhs);
	void setRhs(shared_ptr<IExpressionNode>&& rhs);
	shared_ptr<IExpressionNode>& getLhs(void);
	shared_ptr<IExpressionNode>& getRhs(void);

	void setOperator(string& ope);
	void setOperator(string&& ope);
	string& getOperator(void);

	string toString(void);
	string toSolutionString(void);

protected:
	shared_ptr<IExpressionNode> m_lhs;
	shared_ptr<IExpressionNode> m_rhs;
	string                      m_operator;
};

TermExpressionNode::TermExpressionNode(void)
: m_lhs(nullptr), m_rhs(nullptr), m_operator("")
{
}

TermExpressionNode::~TermExpressionNode(void)
{
}

void TermExpressionNode::setLhs(shared_ptr<IExpressionNode>& lhs)
{
	m_lhs = lhs;
}

void TermExpressionNode::setLhs(shared_ptr<IExpressionNode>&& lhs)
{
	shared_ptr<IExpressionNode>& node = lhs;
	setLhs(node);
}

void TermExpressionNode::setRhs(shared_ptr<IExpressionNode>& rhs)
{
	m_rhs = rhs;
}

void TermExpressionNode::setRhs(shared_ptr<IExpressionNode>&& rhs)
{
	shared_ptr<IExpressionNode>& node = rhs;
	setRhs(node);
}

shared_ptr<IExpressionNode>& TermExpressionNode::getLhs(void)
{
	return m_lhs;
}

shared_ptr<IExpressionNode>& TermExpressionNode::getRhs(void)
{
	return m_rhs;
}

void TermExpressionNode::setOperator(string& ope)
{
	m_operator = ope;
}

void TermExpressionNode::setOperator(string&& ope)
{
	m_operator = ope;
}

string& TermExpressionNode::getOperator(void)
{
	return m_operator;
}

string TermExpressionNode::toString()
{
	return m_lhs->toString() + " " + m_rhs->toString() + " " + m_operator;
}

string TermExpressionNode::toSolutionString()
{
	return "( " + m_lhs->toSolutionString() + " " + m_operator + " " + m_rhs->toSolutionString() + " )";
}

class BinaryExpressionNode: public IExpressionNode
{
public:
	BinaryExpressionNode(void);
	~BinaryExpressionNode(void);

	void setLhs(shared_ptr<IExpressionNode>& lhs);
	void setLhs(shared_ptr<IExpressionNode>&& lhs);
	void setRhs(shared_ptr<IExpressionNode>& rhs);
	void setRhs(shared_ptr<IExpressionNode>&& rhs);
	shared_ptr<IExpressionNode>& getLhs(void);
	shared_ptr<IExpressionNode>& getRhs(void);

	void setOperator(string& ope);
	void setOperator(string&& ope);
	string& getOperator(void);

	string toString(void);
	string toSolutionString(void);

protected:
	shared_ptr<IExpressionNode> m_lhs;
	shared_ptr<IExpressionNode> m_rhs;
	string                      m_operator;
};

BinaryExpressionNode::BinaryExpressionNode(void)
: m_lhs(nullptr), m_rhs(nullptr), m_operator("")
{
}

BinaryExpressionNode::~BinaryExpressionNode(void)
{
}

void BinaryExpressionNode::setLhs(shared_ptr<IExpressionNode>& lhs)
{
	m_lhs = lhs;
}

void BinaryExpressionNode::setLhs(shared_ptr<IExpressionNode>&& lhs)
{
	shared_ptr<IExpressionNode>& node = lhs;
	setLhs(node);
}

void BinaryExpressionNode::setRhs(shared_ptr<IExpressionNode>& rhs)
{
	m_rhs = rhs;
}

void BinaryExpressionNode::setRhs(shared_ptr<IExpressionNode>&& rhs)
{
	shared_ptr<IExpressionNode>& node = rhs;
	setRhs(node);
}

shared_ptr<IExpressionNode>& BinaryExpressionNode::getLhs(void)
{
	return m_lhs;
}

shared_ptr<IExpressionNode>& BinaryExpressionNode::getRhs(void)
{
	return m_rhs;
}

void BinaryExpressionNode::setOperator(string& ope)
{
	m_operator = ope;
}

void BinaryExpressionNode::setOperator(string&& ope)
{
	m_operator = ope;
}

string& BinaryExpressionNode::getOperator(void)
{
	return m_operator;
}

string BinaryExpressionNode::toString()
{
	return m_lhs->toString() + " " + m_rhs->toString() + " " + m_operator;
}

string BinaryExpressionNode::toSolutionString()
{
	return "( " + m_lhs->toSolutionString() + " " + m_operator + " " + m_rhs->toSolutionString() + " )";
}


Tree::Tree(void)
{
}

Tree::~Tree(void)
{
}

void Tree::addExpression(shared_ptr<IExpressionNode> &node)
{
	m_rootNode = node;
}

shared_ptr<IExpressionNode>& Tree::getRootNode(void)
{
	return m_rootNode;
}

Token::Token(TokenType type, string& token)
: m_type(type), m_token(token), m_next(nullptr)
{
}

Token::Token(TokenType type, string&& token)
: m_type(type), m_token(token), m_next(nullptr)
{
}

Token::~Token(void)
{
}

void Token::setNext(shared_ptr<Token>& next)
{
	m_next = next;
}

void Token::setNext(const shared_ptr<Token>&& next)
{
	m_next = next;
}

shared_ptr<Token> Token::getNext(void)
{
	return m_next;
}

TokenType Token::getType(void)
{
	return m_type;
}

string& Token::getToken(void)
{
	return m_token;
}

Tokenizer::Tokenizer(void)
: m_token(nullptr), m_lastToken(m_token)
{}

Tokenizer::~Tokenizer(void)
{}

shared_ptr<Token>& Tokenizer::tokenize(const vector<string>& source)
{
	m_source = source;
	m_iter = m_source.begin();

	m_token = nullptr;

	while (m_iter != m_source.end()) {
		readToken();
	}

	appendToken(make_shared<Token>(EndToken, "End"));

	return m_token;
}

shared_ptr<Token>& Tokenizer::tokenize(const vector<string>&& source)
{
	vector<string>& list = const_cast<vector<string>&>(source);
	return tokenize(list);
}

typedef struct {
	int 	order;
	bool	hasParameter;
} TOKEN_DESCRIPTOR;

const map<string, TOKEN_DESCRIPTOR> operatorOrder = {
	{ "+",			{ 0,  false }			},
	{ "-",			{ 0,  false }			},
	{ "*",			{ 1,  false }			},
	{ "/",			{ 1,  false }			},
	{ "^",			{ 2,  false }			},
	{ "square",		{ 2,  false }			},
	{ "cube",		{ 2,  false }			},
	{ "inverse",	{ 2,  false }			},
	{ "%",			{ 2,  false }			},
	{ "!",			{ 1,  false }			},
	// paren
	{ "(",			{ -1, false }			},
	{ ")",			{ -1, false }			},
	// Special token
	{ ",",			{ 0,  false }			},	// Separate Operator
};
const map<string, TOKEN_DESCRIPTOR> constantOrder = {
	// const value
	{ "M_PI",		{ 0,  false }			},	// Pi
	{ "M_E",		{ 0,  false }			},	// Napier's constant
};
const map<string, TOKEN_DESCRIPTOR> memoryOrder = {
	// Memory value
	{ "MEMORY_M",	{ 0,  false }			},
	{ "MEMORY_X",	{ 0,  false }			},
	{ "MEMORY_Y",	{ 0,  false }			},
	{ "MEMORY_A",	{ 0,  false }			},
	{ "MEMORY_B",	{ 0,  false }			},
	{ "MEMORY_C",	{ 0,  false }			},
	{ "MEMORY_D",	{ 0,  false }			},
	{ "MEMORY_ANS",	{ 0,  false }			},
};
const map<string, TOKEN_DESCRIPTOR> functionOrder = {
	{ "abs",		{ 0x7fffffff, true }	},
	{ "sin",		{ 0x7fffffff, true }	},
	{ "cos",		{ 0x7fffffff, true }	},
	{ "tan",		{ 0x7fffffff, true }	},
	{ "sinh",		{ 0x7fffffff, true }	},
	{ "cosh",		{ 0x7fffffff, true }	},
	{ "tanh",		{ 0x7fffffff, true }	},
	{ "asin",		{ 0x7fffffff, true }	},
	{ "acos",		{ 0x7fffffff, true }	},
	{ "atan",		{ 0x7fffffff, true }	},
	{ "asinh",		{ 0x7fffffff, true }	},
	{ "acosh",		{ 0x7fffffff, true }	},
	{ "atanh",		{ 0x7fffffff, true }	},
	{ "log",		{ 0x7fffffff, true }	},
	{ "ln",			{ 0x7fffffff, true }	},
	{ "LCM",		{ 0x7fffffff, true }	},
	{ "GCD",		{ 0x7fffffff, true }	},
	{ "sqrt",		{ 0x7fffffff, true }	},
	{ "cbrt",		{ 0x7fffffff, true }	},
	{ "Rand",		{ 0x7fffffff, false }	},
	{ "iRand",		{ 0x7fffffff, true }	},
};

extern bool isNumeric(string &token);

bool isOperator(string &token)
{
	return operatorOrder.find(token) != operatorOrder.end();
}

bool isConstant(string &token)
{
	return constantOrder.find(token) != constantOrder.end();
}

bool isMemory(string &token)
{
	return memoryOrder.find(token) != memoryOrder.end();
}

bool isFunction(string &token)
{
	return functionOrder.find(token) != functionOrder.end();
}

void Tokenizer::readToken(void)
{
	if (isNumeric(*m_iter)) {
		appendToken(make_shared<Token>(NumberToken, *m_iter++));
	} else if (isOperator(*m_iter)) {
		appendToken(make_shared<Token>(OperatorToken, *m_iter++));
	} else if (isConstant(*m_iter)) {
		appendToken(make_shared<Token>(ConstantToken, *m_iter++));
	} else if (isMemory(*m_iter)) {
		appendToken(make_shared<Token>(MemoryToken, *m_iter++));
	} else if (isFunction(*m_iter)) {
		appendToken(make_shared<Token>(FunctionToken, *m_iter++));
	} else {
		appendToken(make_shared<Token>(ErrorToken, *m_iter++));
	}
}

void Tokenizer::appendToken(shared_ptr<Token>&& token)
{
	if (m_token != nullptr) {
		m_lastToken->setNext(token);
		m_lastToken = m_lastToken->getNext();
	} else {
		m_token = token;
		m_lastToken = m_token;
	}
}

TokenReader::TokenReader(const shared_ptr<Token>& token)
: m_token(const_cast<shared_ptr<Token>&>(token))
{}

TokenReader::TokenReader(const shared_ptr<Token>&& token)
: m_token(const_cast<shared_ptr<Token>&>(token))
{}

TokenReader::~TokenReader()
{}

bool TokenReader::hasNext(void)
{
	return m_token->getType() != EndToken;
}

string TokenReader::peek(void)
{
	return m_token->getToken();
}

string TokenReader::next(void)
{
	string data = m_token->getToken();
	if (m_token->getType() == ErrorToken) {
		throw SyntaxErrorException("unexpected token : " + data);
	}
	m_token = m_token->getNext();
	return data;
}

string TokenReader::next(const string &&token)
{
	string data = m_token->getToken();
	if (data != token || m_token->getType() == ErrorToken) {
		throw SyntaxErrorException("unexpected token : " + data);
	}
	m_token = m_token->getNext();
	return data;
}

string TokenReader::next(const TokenType type)
{
	string data = m_token->getToken();
	if (m_token->getType() != type || m_token->getType() == ErrorToken) {
		throw SyntaxErrorException("unexpected token : " + data);
	}
	m_token = m_token->getNext();
	return data;
}

bool TokenReader::is(const string &&token)
{
	return m_token->getToken() == token;
}

bool TokenReader::is(const TokenType type)
{
	return m_token->getType() == type;
}

Parser::Parser(void)
: m_tr(nullptr)
{
}

Parser::~Parser(void)
{
}

Tree& Parser::parse(vector<string>& expression)
{
	Tokenizer tokenizer;
	shared_ptr<Token>& token = tokenizer.tokenize(expression);
	m_tr = make_shared<TokenReader>(token);

	shared_ptr<IExpressionNode> node = parseExpression();
	m_tree.addExpression(node);

	m_tr->next(EndToken);

	return m_tree;
}

shared_ptr<IExpressionNode> Parser::parseExpression(void)
{
	/*
	 * <expression> := <term> { <binary> }*;
	 */
	printf("%s\r\n", __FUNCTION__);

	auto node = parseTermExpression();
	return parseBinaryExpression(node, 0);
}

shared_ptr<IExpressionNode> Parser::parseBinaryExpression(shared_ptr<IExpressionNode> lhs, int minPrec)
{
	/*
	 * <binary> := ... { [ ( `+` | `-` | `*` | `/` | `^` ) ] <term> };
	 */
	printf("%s\r\n", __FUNCTION__);

	int prec = -1;

	while (true) {
		string op = "*", nextOp = "";

		if (m_tr->is(OperatorToken) && getPrec(m_tr->peek()) >= 0) {
			// Load current token
			op = m_tr->peek();
		}

		if (m_tr->is(EndToken) || m_tr->is(",") || m_tr->is(")") || (prec = getPrec(op)) < minPrec) {
			// Ended term on this phase
			break;
		}

		if (m_tr->is(OperatorToken) && getPrec(m_tr->peek()) >= 0) {
			// Load next token
			op = m_tr->next(OperatorToken);
		}

		auto rhs = parseTermExpression();

		if (!m_tr->is(EndToken)) {
			if (!m_tr->is(OperatorToken) || getPrec(m_tr->peek()) == -1) {
				nextOp = "*";
			} else {
				nextOp = m_tr->peek();
			}

			if (getPrec(nextOp) > prec) {
				rhs = parseBinaryExpression(rhs, prec + 1);
			}
		}

		auto ben = make_shared<BinaryExpressionNode>();
		ben->setLhs(lhs);
		ben->setOperator(op);
		ben->setRhs(rhs);
		lhs = static_pointer_cast<IExpressionNode>(ben);
	}

	return lhs;
}

shared_ptr<IExpressionNode> Parser::parseTermExpression(void)
{
	/*
	 * <term> := { <unary> }*;
	 */
	printf("%s\r\n", __FUNCTION__);

	shared_ptr<IExpressionNode> en = nullptr;
	en = parseUnaryExpression();
	while (!(m_tr->is("+") || m_tr->is("-") || m_tr->is("*") || m_tr->is("/") || m_tr->is("^") || m_tr->is(")") || m_tr->is(",")) && !m_tr->is(EndToken)) {
		auto ben = make_shared<BinaryExpressionNode>();
		ben->setLhs(en);
		ben->setOperator("*");
		ben->setRhs(parseUnaryExpression());
		en = static_pointer_cast<IExpressionNode>(ben);
	}

	return en;
}

shared_ptr<IExpressionNode> Parser::parseUnaryExpression(void)
{
	/*
	 * <unary> := [ ( `+` | `~` | `-` ) ] ( <function> | <identifier> | <paren> ) [ `!` | `square` | `cube` | `inverse` | `%` ];
	 */
	printf("%s\r\n", __FUNCTION__);

	shared_ptr<UnaryExpressionNode> unaryNode = make_shared<UnaryExpressionNode>();

	unaryNode->setOperator("");
	if (m_tr->is("+")) {
		m_tr->next("+");
	} else if (m_tr->is("-")) {
		m_tr->next("-");
		unaryNode->setOperator("~");
	}

	shared_ptr<IExpressionNode> en = nullptr;

	if (m_tr->is(FunctionToken)) {
		en = parseFunctionExpression();
	} else if (m_tr->is(ConstantToken) || m_tr->is(MemoryToken)) {
		en = parseIdentifierExpression();
	} else if (m_tr->is(NumberToken)) {
		en = parseNumberExpression();
	} else if (m_tr->is("(")) {
		en = parseParenExpression();
	} else {
		throw SyntaxErrorException("unexpected token : " + m_tr->peek());
	}
	
	// 右辺修飾演算子
	if (m_tr->is("!") || m_tr->is("square") || m_tr->is("cube") || m_tr->is("inverse") || m_tr->is("%")) {
		auto node = make_shared<UnaryExpressionNode>();
		auto op = m_tr->next(OperatorToken);
		node->setOperator(op);
		node->setRhs(en);
		en = static_pointer_cast<IExpressionNode>(node);
	}

	unaryNode->setRhs(en);

	return unaryNode;
}

shared_ptr<IExpressionNode> Parser::parseFunctionExpression(void)
{
	/*
	 * <function> := <function_name> [ ( `(` <expression> [ { `,` <expression> } ] `)` ] | <term> );
	 */
	printf("%s\r\n", __FUNCTION__);

	const string& token = m_tr->next(FunctionToken);
	vector<shared_ptr<IExpressionNode>> argument;
	if (functionOrder.at(token).hasParameter) {
		if (m_tr->is("(")) {
			m_tr->next("(");
			argument.push_back(parseExpression());
			while (!m_tr->is(")") && m_tr->is(",")) {
				m_tr->next(",");
				argument.push_back(parseExpression());
			}
			m_tr->next(")");
		} else {
			argument.push_back(parseTermExpression());
		}
	}
	auto node = make_shared<FunctionExpressionNode>();
	node->setFunction(token);
	node->setArgument(argument);
	return static_pointer_cast<IExpressionNode>(node);
}

shared_ptr<IExpressionNode> Parser::parseParenExpression(void)
{
	/*
	 * <paren> := `(` <expression> `)`;
	 */
	printf("%s\r\n", __FUNCTION__);

	m_tr->next("(");
	auto node = parseExpression();
	m_tr->next(")");
	return node;
}

shared_ptr<IExpressionNode> Parser::parseIdentifierExpression(void)
{
	/*
	 * <identifier> := ( <constant> | <memory> | <number> );
	 */
	printf("%s\r\n", __FUNCTION__);

	shared_ptr<IExpressionNode> node = nullptr;

	if (m_tr->is(ConstantToken)) {
		node = parseConstantExpression();
	} else if (m_tr->is(MemoryToken)) {
		node = parseMemoryExpression();
	} else if (m_tr->is(NumberToken)) {
		node = parseNumberExpression();
	} else {
		throw SyntaxErrorException("unexpected token : " + m_tr->peek());
	}

	return node;
}

shared_ptr<IExpressionNode> Parser::parseConstantExpression(void)
{
	/*
	 * <constant> := ( `M_PI` | `M_E` );
	 */
	printf("%s\r\n", __FUNCTION__);

	const string& token = m_tr->next(ConstantToken);
	auto node = make_shared<IdentiferExpressionNode>();
	node->setIdentifer(token);
	return static_pointer_cast<IExpressionNode>(node);
}

shared_ptr<IExpressionNode> Parser::parseMemoryExpression(void)
{
	/*
	 * <memory> := ( `MEMORY_ANS` | `MEMORY_A` | `MEMORY_B` | `MEMORY_C` | `MEMORY_D` | `MEMORY_M` | `MEMORY_X` | `MEMORY_Y` );
	 */
	printf("%s\r\n", __FUNCTION__);

	const string& token = m_tr->next(MemoryToken);
	auto node = make_shared<IdentiferExpressionNode>();
	node->setIdentifer(token);
	return static_pointer_cast<IExpressionNode>(node);
}

shared_ptr<IExpressionNode> Parser::parseNumberExpression(void)
{
	/*
	 * <number> := ( [0-9]+ | [0-9]*\.[0-9]+ | [0-9]*\.[0-9]+e\+[0-9]+ );
	 */
	printf("%s\r\n", __FUNCTION__);

	const string& token = m_tr->next(NumberToken);
	auto node = make_shared<NumberExpressionNode>();
	node->setNumber(token);
	return static_pointer_cast<IExpressionNode>(node);
}

int Parser::getPrec(string& ope)
{
	int result = -1;

	if (operatorOrder.find(ope) != operatorOrder.end()) {
		result = operatorOrder.at(ope).order;
	}

	return result;
}

int Parser::getPrec(string&& ope)
{
	string& temp = ope;
	return getPrec(temp);
}
