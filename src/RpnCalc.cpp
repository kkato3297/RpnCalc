// RpnCalc.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "RpnCalc.h"

#include <Data.h>
#include <In2Rpn/In2Rpn.h>
#include <Rpn/Rpn.h>

using namespace std;

// int wmain(int argc, wchar_t *argv[])
int main(int argc, char *argv[])
{
	Rpn rpn;
	string expr, command("y");

	mpfr_float::default_precision(100);

	do {
		cout << "expression: ";
		getline(cin, expr);

		try {
			// 中間記法から逆ポーランド記法へ変換
			In2Rpn in2rpn(expr);
			expr = in2rpn.toRpn();

			cout << "rpn expr: \"" << expr << "\"" << endl;
			cout << "solution expr: \"" << in2rpn.toSolutionExpression() << "\"" << endl;

			// 実行
			cout << "result: " << std::setprecision(mpfr_float::default_precision()) << rpn.exec(expr) << endl;
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
