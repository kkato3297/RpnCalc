#pragma once

#include <string>
#include <In2Rpn/Parser.h>

using namespace std;

class In2Rpn
{
public:
	In2Rpn(const string &expr);
	virtual ~In2Rpn(void);

	string toRpn(void);
	string toSolutionExpression(void);

private:
	string separateToken(const string &expr);

private:
	Tree m_tokenTree;
};