#pragma once

class Number
{
public:
	Number() : m_value(0) {};
	Number(int value) : m_value(static_cast<double>(value)) {};
	Number(double value) : m_value(value) {};
	virtual ~Number() {};

	operator double() { return m_value; };

private:
	double m_value;
};