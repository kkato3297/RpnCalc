#pragma once

#include <vector>
#include <string>

using namespace std;

class In2Rpn
{
public:
	In2Rpn(const string &expr);
	virtual ~In2Rpn(void);

	string toRpn(void);

private:
	string separateToken(const string &expr);

private:
	vector<string> m_tokenList;
};