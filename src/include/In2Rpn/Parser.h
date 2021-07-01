//
// Created by KK Systems on 2020-01-27.
//

#pragma once

#include <memory>
#include <string>
#include <vector>

using namespace std;

class IExpressionNode
{
public:
	IExpressionNode(void);
	virtual ~IExpressionNode(void);

	virtual string toString(void) = 0;
	virtual string toSolutionString(void) = 0;
};

class Tree
{
public:
	Tree(void);
	~Tree(void);

	void addExpression(shared_ptr<IExpressionNode>& node);
	shared_ptr<IExpressionNode>& getRootNode(void);

private:
	shared_ptr<IExpressionNode> m_rootNode;
};

enum TokenType
{
	NumberToken,
	OperatorToken,
	FunctionToken,
	ConstantToken,
	MemoryToken,
	EndToken,
	ErrorToken,
};

class Token
{
public:
	Token(TokenType type, string& token);
	Token(TokenType type, string&& token);
	~Token(void);

	void setNext(shared_ptr<Token>& next);
	void setNext(const shared_ptr<Token>&& next);
	shared_ptr<Token> getNext(void);

	TokenType getType(void);
	string& getToken(void);

private:
	TokenType   		m_type;
	string      		m_token;
	shared_ptr<Token>	m_next;
};

class Tokenizer
{
public:
	Tokenizer(void);
	~Tokenizer(void);

	shared_ptr<Token>& tokenize(const vector<string>& source);
	shared_ptr<Token>& tokenize(const vector<string>&& source);

private:
	void readToken(void);
	void appendToken(shared_ptr<Token>&& token);

	shared_ptr<Token>   		m_token;
	shared_ptr<Token>  			m_lastToken;
	vector<string> 				m_source;
	vector<string>::iterator	m_iter;
};

class TokenReader
{
public:
	TokenReader(const shared_ptr<Token>& token);
	TokenReader(const shared_ptr<Token>&& token);
	~TokenReader(void);

	bool hasNext(void);
	string peek(void);
	string next(void);
	string next(const string&& token);
	string next(const TokenType type);
	bool is(const string&& token);
	bool is(const TokenType type);

private:
	shared_ptr<Token> m_token;
};

class Parser
{
public:
	Parser(void);
	~Parser(void);

	Tree& parse(vector<string>& expression);

private:
	shared_ptr<IExpressionNode> parseExpression(void);
	shared_ptr<IExpressionNode> parseBinaryExpression(shared_ptr<IExpressionNode> lhs, int minPrec);
	shared_ptr<IExpressionNode> parseTermExpression(void);
	shared_ptr<IExpressionNode> parseUnaryExpression(void);
	shared_ptr<IExpressionNode> parseFunctionExpression(void);
	shared_ptr<IExpressionNode> parseParenExpression(void);
	shared_ptr<IExpressionNode> parseIdentifierExpression(void);
	shared_ptr<IExpressionNode> parseConstantExpression(void);
	shared_ptr<IExpressionNode> parseMemoryExpression(void);
	shared_ptr<IExpressionNode> parseNumberExpression(void);

	int getPrec(string& ope);
	int getPrec(string&& ope);

	Tree                            m_tree;
	shared_ptr<TokenReader>         m_tr;
};
