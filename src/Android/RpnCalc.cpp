//
// Created by KK Systems on 2021/03/16.
//

#include "RpnCalc.h"
#include <In2Rpn/In2Rpn.h>
#include <Rpn/Rpn.h>
#include <Exception.h>

static Rpn rpn;

std::string convIn2Rpn(const std::string &expr)
{
	std::string result = "";
	std::string string = expr;

	In2Rpn in2rpn(string);
	result = in2rpn.toRpn();

	return result;
}

std::string rpnExec(const std::string &expr)
{
	Number result = 0;
	std::string string = expr;

	mpfr_float::default_precision(100);

	result = rpn.exec(string);

	std::stringstream ss;
	ss << std::setprecision(mpfr_float::default_precision()) << result;

	return ss.str();
}
