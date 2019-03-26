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