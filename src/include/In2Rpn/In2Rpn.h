#pragma once

#include <vector>
#include <string>

using namespace std;

class In2Rpn
{
public:
	In2Rpn(string &expr);
	virtual ~In2Rpn(void);

	string toRpn(void);

private:
	string separateToken(string &expr);

private:
	vector<string> m_tokenList;
};