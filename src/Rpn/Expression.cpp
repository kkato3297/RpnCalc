#define _USE_MATH_DEFINES

#include <Rpn/Expression.h>

#include <cmath>

IExpression::IExpression(void)
{}

IExpression::~IExpression(void)
{}

ExpressionCollection::ExpressionCollection(void)
{}

ExpressionCollection::~ExpressionCollection(void)
{}

class Expression_Plus : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number b = stack.pop();
		Number a = stack.pop();

		stack.push(a + b);
	};
};

class Expression_Minus : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number b = stack.pop();
		Number a = stack.pop();

		stack.push(a - b);
	};
};

class Expression_Multiply : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number b = stack.pop();
		Number a = stack.pop();

		stack.push(a * b);
	};
};

class Expression_Division : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number b = stack.pop();
		Number a = stack.pop();

		stack.push(a / b);
	};
};

class Expression_Modulus : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number b = stack.pop();
		Number a = stack.pop();

		stack.push(fmod(a, b));
	};
};

class Expression_Power : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number b = stack.pop();
		Number a = stack.pop();

		stack.push(pow(a, b));
	};
};

class Expression_Factorial : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		// \Gamma(n) = (n - 1)!
		stack.push(tgamma(a + 1));
	};
};

class Expression_Percent : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(a / 100.0);
	};
};

class Expression_Abs : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(abs(a));
	};
};

class Expression_Sin : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(sin(a));
	};
};

class Expression_Cos : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(cos(a));
	};
};

class Expression_Tan : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(tan(a));
	};
};

class Expression_ASin : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(asin(a));
	};
};

class Expression_ACos : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(acos(a));
	};
};

class Expression_ATan : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(atan2(a, 1.0));
	};
};

class Expression_Sinh : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(sinh(a));
	};
};

class Expression_Cosh : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(cosh(a));
	};
};

class Expression_Tanh : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(tanh(a));
	};
};

class Expression_ASinh : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(asinh(a));
	};
};

class Expression_ACosh : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(acosh(a));
	};
};

class Expression_ATanh : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(atanh(a));
	};
};

class Expression_Number : public IExpression {
public:
	Expression_Number(void) : Expression_Number(0) {};
	Expression_Number(Number value) : m_value(value) {};

	virtual void interpret(Stack<Number> &stack) {
		stack.push(m_value);
	};

private:
	Number m_value;
};

static map<string, shared_ptr<IExpression>> s_operatorTable = {
	{ "+",		make_shared<Expression_Plus>()			},
	{ "-",		make_shared<Expression_Minus>()			},
	{ "*",		make_shared<Expression_Multiply>()		},
	{ "/",		make_shared<Expression_Division>()		},
	{ "Mod",	make_shared<Expression_Modulus>()		},
	{ "^",		make_shared<Expression_Power>()			},
	{ "!",		make_shared<Expression_Factorial>()		},
	{ "%",		make_shared<Expression_Percent>()		},
};

static map<string, shared_ptr<IExpression>> s_functionTable = {
	{ "abs",	make_shared<Expression_Abs>()			},
	{ "sin",	make_shared<Expression_Sin>()			},
	{ "cos",	make_shared<Expression_Cos>()			},
	{ "tan",	make_shared<Expression_Tan>()			},
	{ "asin",	make_shared<Expression_ASin>()			},
	{ "acos",	make_shared<Expression_ACos>()			},
	{ "atan",	make_shared<Expression_ATan>()			},
	{ "sinh",	make_shared<Expression_Sinh>()			},
	{ "cosh",	make_shared<Expression_Cosh>()			},
	{ "tanh",	make_shared<Expression_Tanh>()			},
	{ "asinh",	make_shared<Expression_ASinh>()			},
	{ "acosh",	make_shared<Expression_ACosh>()			},
	{ "atanh",	make_shared<Expression_ATanh>()			},
};

static map<string, shared_ptr<IExpression>> s_constantTable = {
	{ "M_PI",	make_shared<Expression_Number>(M_PI)	},
	{ "M_E",	make_shared<Expression_Number>(M_E)		},
};

std::shared_ptr<IExpression> getExpression(string token)
{
	if (s_operatorTable.find(token) != s_operatorTable.end()) {
		return s_operatorTable[token];
	}
	else if (s_functionTable.find(token) != s_functionTable.end()) {
		return s_functionTable[token];
	}
	else if (s_constantTable.find(token) != s_constantTable.end()) {
		return s_constantTable[token];
	}
	else {
		try {
			Expression_Number expression_Number(stod(token));
			return make_shared<Expression_Number>(expression_Number);
		}
		catch (std::invalid_argument &e) {
			throw e;
		}
		catch (std::out_of_range &e) {
			throw e;
		}
	}
}