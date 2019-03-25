#include <Stack.h>

StackOverflowException::StackOverflowException(string what)
: exception(what.c_str())
{}

StackOverflowException::~StackOverflowException(void)
{}