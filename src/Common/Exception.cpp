#include <Stack.h>

#if TARGET_PLATFORM == PLATFORM_IOS
ExceptionCollection::ExceptionCollection(void)
{}

ExceptionCollection::~ExceptionCollection(void)
{}

ExceptionCollection &ExceptionCollection::getInstance(void)
{
	static ExceptionCollection instance;
	return instance;
}

void ExceptionCollection::setException(std::exception *exception)
{
	this->mException = exception;
}

std::exception *ExceptionCollection::getException(void)
{
	return this->mException;
}
#endif

StackOverflowException::StackOverflowException(string what)
        : mWhat(what)
{
#if TARGET_PLATFORM == PLATFORM_IOS
	ExceptionCollection::getInstance().setException(this);
#endif
}

StackOverflowException::~StackOverflowException(void)
{}

const char* StackOverflowException::what() const _NOEXCEPT
{
    return mWhat.c_str();
}

SyntaxErrorException::SyntaxErrorException(string what)
        : mWhat(what)
{
#if TARGET_PLATFORM == PLATFORM_IOS
	ExceptionCollection::getInstance().setException(this);
#endif
}

SyntaxErrorException::~SyntaxErrorException(void)
{}

const char* SyntaxErrorException::what() const _NOEXCEPT
{
    return mWhat.c_str();
}
