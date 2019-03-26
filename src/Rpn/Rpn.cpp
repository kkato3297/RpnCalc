#include <Rpn/Rpn.h>
#include <regex>
#include <iostream>

SyntaxErrorException::SyntaxErrorException(string what)
		: mWhat(what)
{}

SyntaxErrorException::~SyntaxErrorException(void)
{}

const char* SyntaxErrorException::what() const _NOEXCEPT
{
	return mWhat.c_str();
}

Rpn::Rpn(void)
{}

Rpn::~Rpn(void)
{}

Number Rpn::exec(string expr)
{
	Stack<Number> stack;

	try {
		m_expressionCollection.clear();

		parse(expr);

		for (auto &expr : m_expressionCollection) {
			expr->interpret(stack);
		}

		if (stack.length() != 1) {
			throw SyntaxErrorException("Syntax Error");
		}

		return stack.pop();
	}
	catch (StackOverflowException &e) {
		throw e;
	}
	catch (std::exception &e) {
		throw SyntaxErrorException("Syntax Error");
	}
}

void Rpn::parse(string expr)
{
	try {
		regex re(R"((?:([^\s]+))+)");
		sregex_iterator iter(expr.cbegin(), expr.cend(), re);
		sregex_iterator end;

		for (; iter != end; iter++) {
			m_expressionCollection.push_back(getExpression(iter->str()));
		}
	}
	catch (std::exception &e) {
		throw SyntaxErrorException("Syntax Error");
	}
}