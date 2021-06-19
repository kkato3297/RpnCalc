#pragma once

#include <boost/multiprecision/mpfr.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <string>

using namespace boost::multiprecision;

class Number : public mpfr_float
{
public:
	Number() : mpfr_float("0", mpfr_float::default_precision()) {};
	Number(int value) : mpfr_float(static_cast<double>(value), mpfr_float::default_precision()) {};
	Number(double value) : mpfr_float(value, mpfr_float::default_precision()) {};
	Number(const std::string &lvalue) : mpfr_float(lvalue, mpfr_float::default_precision()) {};
	Number(const std::string &&rvalue) : mpfr_float(rvalue, mpfr_float::default_precision()) {};
	Number(const mpfr_float &lvalue) : mpfr_float(lvalue, mpfr_float::default_precision()) {};
	Number(const mpfr_float &&rvalue) : mpfr_float(rvalue, mpfr_float::default_precision()) {};
	virtual ~Number() {};
};

Number operator-(const Number& value1);

Number operator+(const Number& value1, const Number& value2);

Number operator-(const Number& value1, const Number& value2);

Number operator*(const Number& value1, const Number& value2);

Number operator/(const Number& value1, const Number& value2);

bool operator<(const Number& value1, const Number& value2);

bool operator>(const Number& value1, const Number& value2);

bool operator==(const Number& value1, const Number& value2);

bool operator!=(const Number& value1, const Number& value2);

Number fmod(const Number& value1, const Number& value2);

Number pow(const Number& value1, const Number& value2);

Number abs(const Number& value);

Number sin(const Number& value);

Number cos(const Number& value);

Number tan(const Number& value);

Number asin(const Number& value);

Number acos(const Number& value);

Number atan2(const Number& value1, const Number& value2);

Number sinh(const Number& value);

Number cosh(const Number& value);

Number tanh(const Number& value);

Number log10(const Number& value);

Number log(const Number& value);

Number sqrt(const Number& value);

Number LCM(const Number& value1, const Number& value2);

Number LCM(const Number& value1, const Number& value2, const Number& value3);

Number GCD(const Number& value1, const Number& value2);

Number GCD(const Number& value1, const Number& value2, const Number& value3);
