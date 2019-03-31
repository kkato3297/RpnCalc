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
	CPPUNIT_ASSERT(in2rpn.toRpn() == "M_PI sin");
}