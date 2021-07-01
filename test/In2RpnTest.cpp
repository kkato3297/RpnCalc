#include "In2RpnTest.h"
#include <In2Rpn/In2Rpn.h>

void In2RpnTest::setUp(void)
{
}

void In2RpnTest::tearDown(void)
{
}

void In2RpnTest::testcase0001(void) {
	In2Rpn in2rpn(string("2*(3+4*(5+6))"));
	CPPUNIT_ASSERT(in2rpn.toRpn() == "2 3 4 5 6 + * + *");
}

void In2RpnTest::testcase0002(void) {
	In2Rpn in2rpn(string("2*(3+4*(5+6*(7+8)))"));
	CPPUNIT_ASSERT(in2rpn.toRpn() == "2 3 4 5 6 7 8 + * + * + *");
}

void In2RpnTest::testcase0003(void) {
	In2Rpn in2rpn(string("1/3*3"));
	CPPUNIT_ASSERT(in2rpn.toRpn() == "1 3 / 3 *");
}

void In2RpnTest::testcase0004(void) {
	In2Rpn in2rpn(string("1/(3*3)"));
	CPPUNIT_ASSERT(in2rpn.toRpn() == "1 3 3 * /");
}

void In2RpnTest::testcase0005(void) {
	In2Rpn in2rpn(string("M_PI"));
	CPPUNIT_ASSERT(in2rpn.toRpn() == "M_PI");
}

void In2RpnTest::testcase0006(void) {
	In2Rpn in2rpn(string("sin M_PI"));
	CPPUNIT_ASSERT(in2rpn.toRpn() == "M_PI sin@1");
}

void In2RpnTest::testcase0007(void) {
	In2Rpn in2rpn(string("."));
	CPPUNIT_ASSERT(in2rpn.toRpn() == ".");
}

void In2RpnTest::testcase0008(void) {
	In2Rpn in2rpn(string("3."));
	CPPUNIT_ASSERT(in2rpn.toRpn() == "3.");
}

void In2RpnTest::testcase0009(void) {
	In2Rpn in2rpn(string(".5"));
	CPPUNIT_ASSERT(in2rpn.toRpn() == ".5");
}

void In2RpnTest::testcase0010(void) {
	In2Rpn in2rpn(string("2 ( 3 + 4 ( 5 + 6 ( 7 + 8 ) ) )"));
	CPPUNIT_ASSERT(in2rpn.toRpn() == "2 3 4 5 6 7 8 + * + * + *");
}

void In2RpnTest::testcase0011(void) {
	In2Rpn in2rpn(string("6 / 2 (1 + 2)"));
	CPPUNIT_ASSERT(in2rpn.toRpn() == "6 2 1 2 + * /");
}

void In2RpnTest::testcase0012(void) {
	In2Rpn in2rpn(string("sin 2 M_PI"));
	CPPUNIT_ASSERT(in2rpn.toRpn() == "2 M_PI * sin@1");
}
