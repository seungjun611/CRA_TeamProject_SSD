﻿#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../CRA_TeamProject_SSD/TestShell.cpp"
#include "../CRA_TeamProject_SSD/ISSD.h"

using namespace std;
using namespace testing;

const int LBA_COUNT = MAX_LBA - MIN_LBA + 1;

class MockISSD : public ISSD {
public:
	MOCK_METHOD(void, write, (int lba, string data), (override));
	MOCK_METHOD(string, read, (int lba), (override));
};

TEST(TestCaseName, TestName)
{
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(TestShell, CreateObject)
{
	TestShell* shell = new TestShell();
	EXPECT_TRUE(shell);
}
TEST(TestCaseName, ssd_read_expect_value)
{
	MockISSD MockSSD;

	EXPECT_CALL(MockSSD, read(0x10)).WillRepeatedly(Return("0"));
	EXPECT_EQ(MockSSD.read(0x10), "0");
}

TEST(TestCaseName, shell_read_calls_ssd_read_onetime)
{
	TestApplication testApp;
	MockISSD mockSSD;
	testApp.set_ssd(&mockSSD);

	EXPECT_CALL(mockSSD, read(0x10)).Times(1);
	testApp.read(0x10);
}

TEST(TestCaseName, shell_fullread_calls_ssd_read_multiple_times)
{
	TestApplication testApp;
	MockISSD mockSSD;
	testApp.set_ssd(&mockSSD);

	EXPECT_CALL(mockSSD, read(_)).Times(LBA_COUNT);
	testApp.fullread();
}

TEST(TestCaseName, SingleWrite)
{
	MockISSD mock;
	TestShell shell(&mock);

	EXPECT_CALL(mock, write(3, string("0xAAAAAAAA")))
		.Times(1);

	shell.run("write 3 0xAAAAAAAA");
}

TEST(TestCaseName, SingleRead)
{
	MockISSD mock;
	TestShell shell(&mock);

	EXPECT_CALL(mock, read(3))
		.Times(1);

	shell.run("read 3");
}

TEST(MockISSDTest, SSDWriteExcute) {
	MockISSD mock;
	TestApplication ta;
	ta.set_ssd(&mock);

	EXPECT_CALL(mock, write(0, string("0")))
		.Times(1)
		;
	ta.write(0, string("0"));
}

TEST(MockISSDTest, SSDWriteLbaException) {
	MockISSD mock;
	TestApplication ta;
	ta.set_ssd(&mock);

	EXPECT_CALL(mock, write(-1, string("0")))
		.Times(1)
		;
	ta.write(-1, string("0"));

	EXPECT_THROW(ta, exception);
}

TEST(MockISSDTest, SSDWriteLbaException2) {
	MockISSD mock;
	TestApplication ta;
	ta.set_ssd(&mock);

	EXPECT_CALL(mock, write(100, string("0")))
		.Times(1)
		;
	ta.write(100, string("0"));

	EXPECT_THROW(ta, exception);
}

TEST(MockISSDTest, SSDFullWriteSuccess) {
	MockISSD mock;
	TestApplication ta;
	ta.set_ssd(&mock);

	EXPECT_CALL(mock, write(_,string("0")))
		.Times(LBA_COUNT)
		;

	ta.fullwrite(string("0"));
}