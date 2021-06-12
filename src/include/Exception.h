//
// Created by KK Systems on 2019/03/27.
//

#ifndef CALCULATOR_EXCEPTION_H
#define CALCULATOR_EXCEPTION_H

#include <exception>

#ifndef _NOEXCEPT
#define _NOEXCEPT noexcept
#endif

using namespace std;

#if TARGET_PLATFORM == PLATFORM_IOS
class ExceptionCollection
{
private:
	std::exception *mException;

	ExceptionCollection(void);
	~ExceptionCollection(void);

public:
	static ExceptionCollection &getInstance(void);
	void setException(std::exception *exception);
	std::exception *getException(void);
};
#endif

class StackOverflowException : public exception
{
private:
	string mWhat;

public:
	StackOverflowException(string what);
	virtual ~StackOverflowException(void) override;
	virtual const char* what() const _NOEXCEPT override;
};

class SyntaxErrorException : public exception
{
private:
	string mWhat;

public:
	SyntaxErrorException(string what);
	virtual ~SyntaxErrorException(void) override;
	virtual const char* what() const _NOEXCEPT override;
};

#endif //CALCULATOR_EXCEPTION_H
