#pragma once

#include <Stack.h>
#include <vector>
#include <string>
#include <map>
#include <memory>

using namespace std;

class IExpression
{
public:
	IExpression(void);
	virtual ~IExpression(void);

	virtual void interpret(Stack<Number> &stack) = 0;
};

class ExpressionCollection : public vector<std::shared_ptr<IExpression>>
{
public:
	ExpressionCollection(void);
	virtual ~ExpressionCollection(void);
};

std::shared_ptr<IExpression> getExpression(string token);