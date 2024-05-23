﻿#include <vector>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../CRA_TeamProject_SSD/TestShell.cpp"
#include "../CRA_TeamProject_SSD/ShellCommand/WriteCommand.cpp"
#include "../CRA_TeamProject_SSD/ShellCommand/ExitCommand.cpp"
#include "../CRA_TeamProject_SSD/ShellCommand/HelpCommand.cpp"
#include "../CRA_TeamProject_SSD/ShellCommand/ReadCommand.cpp"
#include "../CRA_TeamProject_SSD/ShellCommand/CommandFactory.cpp"
#include "../CRA_TeamProject_SSD/ShellCommand/FullWriteCommand.cpp"
#include "../CRA_TeamProject_SSD/ShellCommand/FullReadCommand.cpp"
#include "../CRA_TeamProject_SSD/ShellCommand/TestApp1Command.cpp"
#include "../CRA_TeamProject_SSD/ShellCommand/TestApp2Command.cpp"
#include "../CRA_TeamProject_SSD/ISSD.h"

using namespace std;
using namespace testing;

int LBA_NORMAL = 23;
int LBA_LESS_THAN_0 = -1;
int LBA_OVER_THAN_99 = 100;

string DATA_NORMAL = "0x11111111";

int LBA_COUNT = MAX_LBA - MIN_LBA + 1;

class MockISSD : public ISSD {
public:
	MOCK_METHOD(void, write, (int lba, string data), (override));
	MOCK_METHOD(string, read, (int lba), (override));
};

class MockTestShell : public TestShell {
public:
	MOCK_METHOD(void, check, (const vector<string>& args), ());

};


class SSDTestFixture : public Test {
public:
	void SetUp() override {
		testApp.set_ssd(&mockISSD);
	}

	TestApplication testApp;

	NiceMock<MockISSD> mockISSD;

	void assertIllegalArgument(string command) {
		TestShell testShell(&mockISSD);
		try {
			testShell.run(command);
			FAIL();
		}
		catch (exception e) {

		}
	}

};



TEST(TestShell, CreateObject)
{
	TestShell* shell = new TestShell();
	EXPECT_TRUE(shell);
}

TEST_F(SSDTestFixture, ssd_read_expect_value)
{
	EXPECT_CALL(mockISSD, read(LBA_NORMAL)).WillRepeatedly(Return("0"));
	EXPECT_EQ(mockISSD.read(LBA_NORMAL), "0");
}

TEST_F(SSDTestFixture, shell_read_calls_ssd_read_onetime)
{
	EXPECT_CALL(mockISSD, read(LBA_NORMAL)).Times(1);
	testApp.read(LBA_NORMAL);
}

TEST_F(SSDTestFixture, shell_fullread_calls_ssd_read_multiple_times)
{
	EXPECT_CALL(mockISSD, read(_)).Times(LBA_COUNT);
	testApp.fullread();
}

TEST_F(SSDTestFixture, SimpleWrite)
{
	TestShell testShell(&mockISSD);

	EXPECT_CALL(mockISSD, write(LBA_NORMAL, DATA_NORMAL))
    .Times(1);

	testShell.run("write " + to_string(LBA_NORMAL) + " " + DATA_NORMAL);
}


TEST_F(SSDTestFixture, SingleRead)
{
	TestShell testShell(&mockISSD);

	EXPECT_CALL(mockISSD, read(3))
		.Times(1);

	testShell.run("read 3");
}


TEST_F(SSDTestFixture, ISSDTest_Write_Excute) {

	EXPECT_CALL(mockISSD, write(LBA_NORMAL, DATA_NORMAL))
		.Times(1)
		;
	testApp.write(LBA_NORMAL, DATA_NORMAL);
}

TEST_F(SSDTestFixture, ISSDTest_FullWrite_Success) {

	EXPECT_CALL(mockISSD, write(_, DATA_NORMAL))
		.Times(LBA_COUNT)
		;

	testApp.fullwrite(DATA_NORMAL);
}


TEST_F(SSDTestFixture, ExceptionTest_Command_InvalidArgument)
{
	assertIllegalArgument("InvalidCommand");
	assertIllegalArgument("read 1 1 1");
	assertIllegalArgument("read -1");
	assertIllegalArgument("read 101");
	assertIllegalArgument("read x");
	assertIllegalArgument("write 1 1 1");
	assertIllegalArgument("write -1 0x11111111");
	assertIllegalArgument("write 101 0x11111111");
	assertIllegalArgument("write x 0x11111111");
	assertIllegalArgument("write 1 0x111111111");
	assertIllegalArgument("write 1 11111111");
}

TEST_F(SSDTestFixture, ISSDTest_TestApp1Write_Success) {

	EXPECT_CALL(mockISSD, write(_,_))
		.Times(LBA_COUNT)
		;

	testApp.runTestApp1();
}

TEST_F(SSDTestFixture, ISSDTest_TestApp2ReadWrite_Success) {

	EXPECT_CALL(mockISSD, write(_,_))
		.Times(186)
		;

	EXPECT_CALL(mockISSD, read(_))
		.Times(6)
		.WillRepeatedly(Return(string("12345678")))
		;

	EXPECT_EQ(true, testApp.runTestApp2());
}

TEST_F(SSDTestFixture, ISSDTest_TestApp2Read_False) {

	EXPECT_CALL(mockISSD, read(_))
		.Times(2)
		.WillOnce(Return(string("12345678")))
		.WillOnce(Return(string("AAAABBBB")))
		;
	
	EXPECT_EQ(false, testApp.runTestApp2());
}

