#include <Utility.h>

string join(vector<string> &list, const string &spliter)
{
	string buffer = "";

	for (auto iter = list.begin(); iter < list.end(); iter++) {
		buffer += (*iter);

		if (iter < list.end() - 1) {
			buffer += spliter;
		}
	}

	return buffer;
}
