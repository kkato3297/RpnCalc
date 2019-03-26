#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TextOutputter.h>

class In2RpnTest : public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE(In2RpnTest);
	CPPUNIT_TEST(testcase0001);
	CPPUNIT_TEST(testcase0002);
	CPPUNIT_TEST(testcase0003);
	CPPUNIT_TEST(testcase0004);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void);

private:
	void testcase0001(void);
	void testcase0002(void);
	void testcase0003(void);
	void testcase0004(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(In2RpnTest);