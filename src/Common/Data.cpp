#include <Data.h>

Number operator-(const Number& value1) {
   return Number(-static_cast<mpfr_float>(value1));
}

Number operator+(const Number& value1, const Number& value2) {
   return Number(static_cast<mpfr_float>(value1) + static_cast<mpfr_float>(value2));
}

Number operator-(const Number& value1, const Number& value2) {
   return Number(static_cast<mpfr_float>(value1) - static_cast<mpfr_float>(value2));
}

Number operator*(const Number& value1, const Number& value2) {
   return Number(static_cast<mpfr_float>(value1) * static_cast<mpfr_float>(value2));
}

Number operator/(const Number& value1, const Number& value2) {
   return Number(static_cast<mpfr_float>(value1) / static_cast<mpfr_float>(value2));
}

Number fmod(const Number& value1, const Number& value2) {
	mpfr_float result = fmod(static_cast<mpfr_float>(value1), static_cast<mpfr_float>(value2));
	return Number(result);
}

Number pow(const Number& value1, const Number& value2) {
	mpfr_float result = pow(static_cast<mpfr_float>(value1), static_cast<mpfr_float>(value2));
	return Number(result);
}

Number abs(const Number& value) {
	mpfr_float result = abs(static_cast<mpfr_float>(value));
	return Number(result);
}

Number sin(const Number& value) {
	mpfr_float result = boost::math::sin_pi(static_cast<mpfr_float>(value) / boost::math::constants::pi<mpfr_float>());
	return Number(result);
}

Number cos(const Number& value) {
	mpfr_float result = boost::math::cos_pi(static_cast<mpfr_float>(value) / boost::math::constants::pi<mpfr_float>());
	return Number(result);
}

Number tan(const Number& value) {
	return sin(value) / cos(value);
}

Number asin(const Number& value) {
	mpfr_float result = asin(static_cast<mpfr_float>(value));
	return Number(result);
}

Number acos(const Number& value) {
	mpfr_float result = acos(static_cast<mpfr_float>(value));
	return Number(result);
}

Number atan2(const Number& value1, const Number& value2) {
	mpfr_float result = atan2(static_cast<mpfr_float>(value1), static_cast<mpfr_float>(value2));
	return Number(result);
}

Number sinh(const Number& value) {
	mpfr_float result = sinh(static_cast<mpfr_float>(value));
	return Number(result);
}

Number cosh(const Number& value) {
	mpfr_float result = cosh(static_cast<mpfr_float>(value));
	return Number(result);
}

Number tanh(const Number& value) {
	mpfr_float result = tanh(static_cast<mpfr_float>(value));
	return Number(result);
}

Number log10(const Number& value) {
	mpfr_float result = log10(static_cast<mpfr_float>(value));
	return Number(result);
}

Number log(const Number& value) {
	mpfr_float result = log(static_cast<mpfr_float>(value));
	return Number(result);
}

Number sqrt(const Number& value) {
	mpfr_float result = sqrt(static_cast<mpfr_float>(value));
	return Number(result);
}

Number LCM(const Number& value1, const Number& value2) {
	mpz_int result = lcm(static_cast<mpz_int>(value1), static_cast<mpz_int>(value2));
	return Number(result);
}

Number LCM(const Number& value1, const Number& value2, const Number& value3) {
	mpz_int result = lcm(static_cast<mpz_int>(value1), static_cast<mpz_int>(value2));
	result = lcm(result, static_cast<mpz_int>(value3));
	return Number(result);
}

Number GCD(const Number& value1, const Number& value2) {
	mpz_int result = gcd(static_cast<mpz_int>(value1), static_cast<mpz_int>(value2));
	return Number(result);
}

Number GCD(const Number& value1, const Number& value2, const Number& value3) {
	mpz_int result = gcd(static_cast<mpz_int>(value1), static_cast<mpz_int>(value2));
	result = gcd(result, static_cast<mpz_int>(value3));
	return Number(result);
}
