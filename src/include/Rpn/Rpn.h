#pragma once

#include <string>
#include <vector>

#include <Stack.h>
#include <Rpn/Expression.h>

using namespace std;

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