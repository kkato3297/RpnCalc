//
// Created by KK Systems on 2020-01-27.
//

#include "Parser.h"
#include <Exception.h>
#include <map>

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
	return m_rhs->toString() + " " + m_operator;
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

class IdentiferExpressionNode: public IExpressionNode
{
public:
	IdentiferExpressionNode(void);
	~IdentiferExpressionNode(void);

	void setIdentifer(const string& num);
	void setIdentifer(const string&& num);
	string& getIdentifer(void);

	string toString(void);

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

	appendToken(make_shared<Token>(End, "End"));

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
const map<string, TOKEN_DESCRIPTOR> identifierOrder = {
	// const value
	{ "M_PI",		{ 0,  false }			},	// Pi
	{ "M_E",		{ 0,  false }			},	// Napier's constant
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

bool isIdentifier(string &token)
{
	return identifierOrder.find(token) != identifierOrder.end();
}

bool isFunction(string &token)
{
	return functionOrder.find(token) != functionOrder.end();
}

void Tokenizer::readToken(void)
{
	if (isNumeric(*m_iter)) {
		appendToken(make_shared<Token>(Number, *m_iter++));
	} else if (isOperator(*m_iter)) {
		appendToken(make_shared<Token>(Operator, *m_iter++));
	} else if (isIdentifier(*m_iter)) {
		appendToken(make_shared<Token>(Identifier, *m_iter++));
	} else if (isFunction(*m_iter)) {
		appendToken(make_shared<Token>(Function, *m_iter++));
	} else {
		appendToken(make_shared<Token>(Error, *m_iter++));
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
	return m_token->getType() != End;
}

string TokenReader::peek(void)
{
	return m_token->getToken();
}

string TokenReader::next(void)
{
	string data = m_token->getToken();
	if (m_token->getType() == Error) {
		throw SyntaxErrorException("unexpected token : " + data);
	}
	m_token = m_token->getNext();
	return data;
}

string TokenReader::next(const string &&token)
{
	string data = m_token->getToken();
	if (data != token || m_token->getType() == Error) {
		throw SyntaxErrorException("unexpected token : " + data);
	}
	m_token = m_token->getNext();
	return data;
}

string TokenReader::next(const TokenType type)
{
	string data = m_token->getToken();
	if (m_token->getType() != type || m_token->getType() == Error) {
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

	m_tr->next(End);

	return m_tree;
}

shared_ptr<IExpressionNode> Parser::parseExpression(void)
{
	/*
	 * <expression> := <unary> { [ ( `+` | `-` | `*` | `/` ) ] <term> };
	 */
	printf("%s\r\n", __FUNCTION__);

	auto node = parseUnaryExpression();
	return parseBinaryExpression(node, 0);
}

shared_ptr<IExpressionNode> Parser::parseUnaryExpression(void)
{
	/*
	 * <unary> := [ ( `+` | `-` ) ] <term>;
	 */
	printf("%s\r\n", __FUNCTION__);

	shared_ptr<IExpressionNode> en = nullptr;
	if (m_tr->is("+")) {
		m_tr->next("+");
	} else if (m_tr->is("-")) {
		auto node = make_shared<UnaryExpressionNode>();
		m_tr->next("-");
		node->setOperator("~");
		node->setRhs(parseTermExpression());
		en = static_pointer_cast<IExpressionNode>(node);
	}

	if (!en) {
		en = parseTermExpression();
	}

	return en;
}

shared_ptr<IExpressionNode> Parser::parseTermExpression(void)
{
	/*
	 * <term> := ( <function> | <identifier> | <number> | `(` <expression> `)` ) [ `!` | `square` | `cube` | `inverse` ];
	 */
	printf("%s\r\n", __FUNCTION__);

	shared_ptr<IExpressionNode> en = nullptr;
	if (m_tr->is(Function)) {
		en = parseFunctionExpression();
	} else if (m_tr->is(Identifier)) {
		en = parseIdentifierExpression();
	} else if (m_tr->is(Number)) {
		en = parseNumberExpression();
	} else if (m_tr->is("(")) {
		en = parseParenExpression();
	} else {
		throw SyntaxErrorException("unexpected token : " + m_tr->peek());
	}
	
	// 右辺修飾演算子
	if (m_tr->is("!") || m_tr->is("square") || m_tr->is("cube") || m_tr->is("inverse") || m_tr->is("%")) {
		auto node = make_shared<UnaryExpressionNode>();
		auto op = m_tr->next(Operator);
		node->setOperator(op);
		node->setRhs(en);
		en = static_pointer_cast<IExpressionNode>(node);
	}

	return en;
}

shared_ptr<IExpressionNode> Parser::parseFunctionExpression(void)
{
	/*
	 * <function> := <function_name> [ ( `(` <expr> [ { `,` <expr> } ] `)` ] | <unary> )
	 */
	printf("%s\r\n", __FUNCTION__);

	const string& token = m_tr->next(Function);
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
			argument.push_back(parseUnaryExpression());
		}
	}
	auto node = make_shared<FunctionExpressionNode>();
	node->setFunction(token);
	node->setArgument(argument);
	return static_pointer_cast<IExpressionNode>(node);
}

shared_ptr<IExpressionNode> Parser::parseIdentifierExpression(void)
{
	/*
	 * <identifier>;
	 */
	printf("%s\r\n", __FUNCTION__);

	const string& token = m_tr->next(Function);
	auto node = make_shared<IdentiferExpressionNode>();
	node->setIdentifer(token);
	return static_pointer_cast<IExpressionNode>(node);
}

shared_ptr<IExpressionNode> Parser::parseNumberExpression(void)
{
	/*
	 * <number>;
	 */
	printf("%s\r\n", __FUNCTION__);

	const string& token = m_tr->next(Number);
	auto node = make_shared<NumberExpressionNode>();
	node->setNumber(token);
	return static_pointer_cast<IExpressionNode>(node);
}

shared_ptr<IExpressionNode> Parser::parseParenExpression(void)
{
	/*
	 * `(` <expr> `)`;
	 */
	printf("%s\r\n", __FUNCTION__);

	m_tr->next("(");
	auto node = parseExpression();
	m_tr->next(")");
	return node;
}

shared_ptr<IExpressionNode> Parser::parseBinaryExpression(shared_ptr<IExpressionNode> lhs, int minPrec)
{
	/*
	 * ... { [ ( `+` | `-` | `*` | `/` ) ] <term> };
	 */
	printf("%s\r\n", __FUNCTION__);

	int prec = -1;

	while (true) {
		string op = "*", nextOp = "";

		if (m_tr->is(Operator) && getPrec(m_tr->peek()) >= 0) {
			// Load current token
			op = m_tr->peek();
		}

		if (m_tr->is(End) || m_tr->is(",") || m_tr->is(")") || (prec = getPrec(op)) < minPrec) {
			// Ended term on this phase
			break;
		}

		if (m_tr->is(Operator) && getPrec(m_tr->peek()) >= 0) {
			// Load next token
			op = m_tr->next(Operator);
		}

		auto rhs = parseTermExpression();

		if (!m_tr->is(Operator) || getPrec(m_tr->peek()) == -1) {
			nextOp = "*";
		} else {
			nextOp = m_tr->peek();
		}

		if (getPrec(nextOp) > prec) {
			rhs = parseBinaryExpression(rhs, prec + 1);
		}

		auto ben = make_shared<BinaryExpressionNode>();
		ben->setLhs(lhs);
		ben->setOperator(op);
		ben->setRhs(rhs);
		lhs = static_pointer_cast<IExpressionNode>(ben);
	}

	return lhs;
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
