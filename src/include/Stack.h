#pragma once

#include <Spec.h>
#include <Data.h>

#include <string>
#include <vector>
#include <exception>

using namespace std;

class StackOverflowException : public exception
{
private:
	string mWhat;

public:
	StackOverflowException(string what);
	virtual ~StackOverflowException(void) override;
	virtual const char* what() const _NOEXCEPT;
};

template<class T>
class Stack
{
public:
	void push(T value)
	{
		m_list.push_back(value);
	};
	T pop(void)
	{
		if (m_list.empty()) {
			throw StackOverflowException("StackOverflowException");
		}

		T value = m_list.back();

		m_list.pop_back();

		return value;
	};
	T back(void)
	{
		return m_list.back();
	};
	size_t length(void)
	{
		return m_list.size();
	};

private:
	std::vector<T> m_list;
};