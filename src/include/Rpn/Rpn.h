#pragma once

#include <string>
#include <vector>

#include <Stack.h>
#include <Rpn/Expression.h>

using namespace std;

class SyntaxErrorException : public exception
{
private:
	string mWhat;

public:
	SyntaxErrorException(string what);
	virtual ~SyntaxErrorException(void) override;
	virtual const char* what() const _NOEXCEPT;
};

class Rpn
{
public:
	Rpn(void);
	virtual ~Rpn(void);

	Number exec(string expr);

private:
	void parse(string expr);

private:
	ExpressionCollection m_expressionCollection;
};