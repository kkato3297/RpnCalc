#define _USE_MATH_DEFINES

#include <Rpn/Expression.h>

#include <cmath>
#include <random>


static int64_t EuclideanAlgorithm(const int64_t a, const int64_t b)
{
	return b == 0 ? a : EuclideanAlgorithm(b, a % b);
}

static int64_t GCD(const int64_t a, const int64_t b)
{
	return EuclideanAlgorithm(a, b);
}

static int64_t GCD(const int64_t a, const int64_t b, const int64_t c)
{
	return GCD(GCD(a, b), c);
}

static int64_t LCM(const int64_t a, const int64_t b)
{
	return a * b / GCD(a, b);
}

static int64_t LCM(const int64_t a, const int64_t b, const int64_t c)
{
	return LCM(LCM(a, b), c);
}


IExpression::IExpression(void)
{}

IExpression::~IExpression(void)
{}

ExpressionCollection::ExpressionCollection(void)
{}

ExpressionCollection::~ExpressionCollection(void)
{}

class Expression_UnaryMinus : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(-a);
	};
};

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

class Expression_Log : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(log10(a));
	};
};

class Expression_Ln : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(log(a));
	};
};

class Expression_LCM_2 : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number b = stack.pop();
		Number a = stack.pop();

		stack.push(static_cast<double>(LCM(a, b)));
	};
};

class Expression_LCM_3 : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number c = stack.pop();
		Number b = stack.pop();
		Number a = stack.pop();

		stack.push(static_cast<double>(LCM(a, b, c)));
	};
};

class Expression_GCD_2 : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number b = stack.pop();
		Number a = stack.pop();

		stack.push(static_cast<double>(GCD(a, b)));
	};
};

class Expression_GCD_3 : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number c = stack.pop();
		Number b = stack.pop();
		Number a = stack.pop();

		stack.push(static_cast<double>(GCD(a, b, c)));
	};
};

class Expression_Sqrt : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(sqrt(a));
	};
};

class Expression_Cbrt : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(cbrt(a));
	};
};

class Expression_Square : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(pow(a, 2));
	};
};

class Expression_Cube : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number a = stack.pop();

		stack.push(pow(a, 3));
	};
};

class Expression_Rand : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());
		std::uniform_real_distribution<double> randomDoubleDistribution(0.0, 1.0);

		stack.push(randomDoubleDistribution(engine));
	};
};

class Expression_IRand : public IExpression {
public:
	virtual void interpret(Stack<Number> &stack) {
		Number b = stack.pop();
		Number a = stack.pop();

		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());
		std::uniform_int_distribution<int> randomIntDistribution(static_cast<int>(a), static_cast<int>(b));

		stack.push(randomIntDistribution(engine));
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
	{ "~",			make_shared<Expression_UnaryMinus>()	},
	{ "+",			make_shared<Expression_Plus>()			},
	{ "-",			make_shared<Expression_Minus>()			},
	{ "*",			make_shared<Expression_Multiply>()		},
	{ "/",			make_shared<Expression_Division>()		},
	{ "Mod",		make_shared<Expression_Modulus>()		},
	{ "^",			make_shared<Expression_Power>()			},
	{ "!",			make_shared<Expression_Factorial>()		},
	{ "%",			make_shared<Expression_Percent>()		},
	{ "square",		make_shared<Expression_Square>()		},
	{ "cube",		make_shared<Expression_Cube>()			},
};

static map<string, shared_ptr<IExpression>> s_functionTable = {
	{ "abs@1",		make_shared<Expression_Abs>()			},
	{ "sin@1",		make_shared<Expression_Sin>()			},
	{ "cos@1",		make_shared<Expression_Cos>()			},
	{ "tan@1",		make_shared<Expression_Tan>()			},
	{ "asin@1",		make_shared<Expression_ASin>()			},
	{ "acos@1",		make_shared<Expression_ACos>()			},
	{ "atan@1",		make_shared<Expression_ATan>()			},
	{ "sinh@1",		make_shared<Expression_Sinh>()			},
	{ "cosh@1",		make_shared<Expression_Cosh>()			},
	{ "tanh@1",		make_shared<Expression_Tanh>()			},
	{ "asinh@1",	make_shared<Expression_ASinh>()			},
	{ "acosh@1",	make_shared<Expression_ACosh>()			},
	{ "atanh@1",	make_shared<Expression_ATanh>()			},
	{ "log@1",		make_shared<Expression_Log>()			},
	{ "ln@1",		make_shared<Expression_Ln>()			},
	{ "LCM@2",		make_shared<Expression_LCM_2>()			},
	{ "LCM@3",		make_shared<Expression_LCM_3>()			},
	{ "GCD@2",		make_shared<Expression_GCD_2>()			},
	{ "GCD@3",		make_shared<Expression_GCD_3>()			},
	{ "sqrt@1",		make_shared<Expression_Sqrt>()			},
	{ "cbrt@1",		make_shared<Expression_Cbrt>()			},
	{ "Rand@0",		make_shared<Expression_Rand>()			},
	{ "iRand@2",	make_shared<Expression_IRand>()			},
};

static map<string, shared_ptr<IExpression>> s_constantTable = {
	{ "M_PI",		make_shared<Expression_Number>(M_PI)	},
	{ "M_E",		make_shared<Expression_Number>(M_E)		},
};

static map<string, shared_ptr<IExpression>> s_memoryTable = {
	{ "MEMORY_A",	make_shared<Expression_Number>(M_PI)	},
	{ "MEMORY_B",	make_shared<Expression_Number>(M_E)		},
	{ "MEMORY_C",	make_shared<Expression_Number>(M_PI)	},
	{ "MEMORY_D",	make_shared<Expression_Number>(M_E)		},
	{ "MEMORY_X",	make_shared<Expression_Number>(M_PI)	},
	{ "MEMORY_Y",	make_shared<Expression_Number>(M_E)		},
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
	else if (s_memoryTable.find(token) != s_memoryTable.end()) {
		return s_memoryTable[token];
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