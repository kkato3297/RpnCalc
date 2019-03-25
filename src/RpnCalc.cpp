// RpnCalc.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "RpnCalc.h"

#include <Data.h>
#include <In2Rpn/In2Rpn.h>
#include <Rpn/Rpn.h>

using namespace std;

int wmain(int argc, wchar_t *argv[])
{
	Rpn rpn;
	string expr, command("y");

	do {
		cout << "expression: ";
		getline(cin, expr);

		try {
			// 中間記法から逆ポーランド記法へ変換
			In2Rpn in2rpn(expr);
			expr = in2rpn.toRpn();

			cout << "rpn expr: \"" << expr << "\"" << endl;

			// 実行
			cout << "result: " << rpn.exec(expr) << endl;
		}
		catch (StackOverflowException &e) {
			cout << "Stack OverFlow: " << e.what() << endl;
		}
		catch (SyntaxErrorException &e) {
			cout << "Syntax Error: " << e.what() << endl;
		};

		cout << endl;
		cout << "continue?? (y/n)";
		getline(cin, command);
		cout << endl;
	} while (command != "n");

	return 0;
}
