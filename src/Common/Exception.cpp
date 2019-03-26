#include <Stack.h>

StackOverflowException::StackOverflowException(string what)
        : mWhat(what)
{}

StackOverflowException::~StackOverflowException(void)
{}

const char* StackOverflowException::what() const _NOEXCEPT
{
    return mWhat.c_str();
}

SyntaxErrorException::SyntaxErrorException(string what)
        : mWhat(what)
{}

SyntaxErrorException::~SyntaxErrorException(void)
{}

const char* SyntaxErrorException::what() const _NOEXCEPT
{
    return mWhat.c_str();
}