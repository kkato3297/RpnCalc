//
// Created by KK Systems on 2021/03/16.
//

#include "RpnCalc.h"
#include <In2Rpn/In2Rpn.h>
#include <Rpn/Rpn.h>
#include <Exception.h>

static Rpn rpn;

std::string convIn2Rpn(std::string expr)
{
	std::string result = "";
	std::string string = expr;

	In2Rpn in2rpn(string);
	result = in2rpn.toRpn();

	return result;
}

double rpnExec(std::string expr)
{
	double result = 0;
	std::string string = expr;

	result = rpn.exec(string);

	return result;
}

std::exception &getException(void)
{
	return *ExceptionCollection::getInstance().getException();
}
