#include <vector>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../CRA_TeamProject_SSD/TestShell.cpp"
#include "../CRA_TeamProject_SSD/WriteCommand.cpp"
#include "../CRA_TeamProject_SSD/CommandFactory.cpp"
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

class ISSDTestFixture : public Test {
public:
	void SetUp() override {
		testApp.set_ssd(&mockISSD);
	}

	TestApplication testApp;
	MockISSD mockISSD;

};

class TestShellTestFixture : public Test {
public:
	void SetUp() override {
		//TestShell testShell(&mockISSD);
	}

	TestShell testShell;
	MockISSD mockISSD;

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

TEST_F(ISSDTestFixture, ssd_read_expect_value)
{
	EXPECT_CALL(mockISSD, read(LBA_NORMAL)).WillRepeatedly(Return("0"));
	EXPECT_EQ(mockISSD.read(LBA_NORMAL), "0");
}

TEST_F(ISSDTestFixture, shell_read_calls_ssd_read_onetime)
{
	EXPECT_CALL(mockISSD, read(LBA_NORMAL)).Times(1);
	testApp.read(LBA_NORMAL);
}

TEST_F(ISSDTestFixture, shell_fullread_calls_ssd_read_multiple_times)
{
	EXPECT_CALL(mockISSD, read(_)).Times(LBA_COUNT);
	testApp.fullread();
}

TEST_F(TestShellTestFixture, SimpleWrite)
{
	TestShell testShell(&mockISSD);

	EXPECT_CALL(mockISSD, write(LBA_NORMAL, DATA_NORMAL))
    .Times(1);

	testShell.run("write " + to_string(LBA_NORMAL) + " " + DATA_NORMAL);
}


TEST_F(TestShellTestFixture, SingleRead)
{
	TestShell testShell(&mockISSD);

	EXPECT_CALL(mockISSD, read(3))
		.Times(1);

	testShell.run("read 3");
}


TEST_F(ISSDTestFixture, SSDWriteExcute) {

	EXPECT_CALL(mockISSD, write(LBA_NORMAL, DATA_NORMAL))
		.Times(1)
		;
	testApp.write(LBA_NORMAL, DATA_NORMAL);
}

TEST_F(ISSDTestFixture, SSDFullWriteSuccess) {

	EXPECT_CALL(mockISSD, write(_, DATA_NORMAL))
		.Times(LBA_COUNT)
		;

	testApp.fullwrite(DATA_NORMAL);
}


TEST(TestShellTest, ExceptionTest_Command_InvalidCommand)
{
	TestShell testshell;

	string command = "InvalidCommand";

	EXPECT_THROW(testshell.run(command), invalid_argument);
}


TEST(TestShellTest, ExceptionTest_ReadCommand_InvalidArgsSize)
{
	TestShell testshell;

	string command = "read 1 1 1";

	EXPECT_THROW(testshell.run(command), invalid_argument);
}


TEST(TestShellTest, ExceptionTest_ReadCommand_InvalidLba)
{
	TestShell testshell;

	string command = "read -1";

	EXPECT_THROW(testshell.run(command), invalid_argument);

	command = "read 101";
	EXPECT_THROW(testshell.run(command), invalid_argument);

	command = "read x";
	EXPECT_THROW(testshell.run(command), invalid_argument);
}

TEST(TestShellTest, ExceptionTest_WriteCommand_InvalidArgsSize)
{
	MockISSD mock_ssd;
	TestShell testshell(&mock_ssd);

	string command = "write 1 1 1";

	EXPECT_THROW(testshell.run(command), invalid_argument);
}


TEST(TestShellTest, ExceptionTest_WriteCommand_InvalidLba)
{
	MockISSD mock_ssd;
	TestShell testshell(&mock_ssd);

	string command = "write -1 0x11111111";

	EXPECT_THROW(testshell.run(command), invalid_argument);

	command = "write 101 0x11111111";
	EXPECT_THROW(testshell.run(command), invalid_argument);

	command = "write x 0x11111111";
	EXPECT_THROW(testshell.run(command), invalid_argument);
}

TEST(TestShellTest, ExceptionTest_WriteCommand_InvalidData)
{
	MockISSD mock_ssd;
	TestShell testshell(&mock_ssd);

	string command = "write 1 0x111111111";

	EXPECT_THROW(testshell.run(command), invalid_argument);

	command = "write 1 11111111";
	EXPECT_THROW(testshell.run(command), invalid_argument);
}