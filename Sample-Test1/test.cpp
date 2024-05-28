#include <vector>
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
#include "../CRA_TeamProject_SSD/ShellCommand/EraseRangeCommand.cpp"
#include "../CRA_TeamProject_SSD/ShellCommand/EraseSizeCommand.cpp"
#include "../CRA_TeamProject_SSD/ShellCommand/FlushCommand.cpp"
#include "../CRA_TeamProject_SSD/Application/ApplicationFactory.cpp"
#include "../CRA_TeamProject_SSD/Application/TestApp1.cpp"
#include "../CRA_TeamProject_SSD/Application/TestApp2.cpp"
#include "../CRA_TeamProject_SSD/Application/FullWriteReadCompare.cpp"
#include "../CRA_TeamProject_SSD/Application/FullRead10AndCompare.cpp"
#include "../CRA_TeamProject_SSD/Application/Runner.cpp"
#include "../CRA_TeamProject_SSD/Application/TestApplication.h"
#include "../SSD/VirtualSSD.cpp"
#include "../SSD/ISSD.h"
#include "../CRA_TeamProject_SSD/Logger.cpp"

using namespace std;
using namespace testing;

const int LBA_NORMAL = 23;
const int LBA_LESS_THAN_0 = -1;
const int LBA_OVER_THAN_99 = 100;

const string DATA_NORMAL = "0x11111111";

class MockISSD : public ISSD {
public:
	~MockISSD() override {}
	MOCK_METHOD(void, write, (int lba, string data), (override));
	MOCK_METHOD(string, read, (int lba), (override));
	MOCK_METHOD(bool, execute, (SSDCommand command), (override));
	MOCK_METHOD(bool, erase, (int lba, int size), (override));
	MOCK_METHOD(bool, flush, (), (override));
	MOCK_METHOD(const char*, getReadFileName, (), (override));
};

class MockTestShell : public TestShell {
public:
	MOCK_METHOD(void, check, (const vector<string>& args), ());

};

class SSDTestFixture : public Test {
public:
	void SetUp() override {
		testApp = new TestApplication(&mockISSD);
		LBA_COUNT = mockISSD.getMaxLBA() - mockISSD.getMinLBA() + 1;
	}

	NiceMock<MockISSD> mockISSD;
	TestApplication* testApp;
	int LBA_COUNT;

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

class VirtualSSDTestFixture : public Test {
public:
	void SetUp() override {
		testApp = new TestApplication(&virtualSSD);
	}

	SSDCommand generateReadCmd(int lba) {
		return SSDCommand{ OPCODE::R, lba, "", 0 };
	}

	SSDCommand generateWriteCmd(int lba, string data) {
		return SSDCommand{ OPCODE::W, lba, data, 0 };
	}

	TestApplication* testApp;
	VirtualSSD virtualSSD;
};

TEST_F(SSDTestFixture, ISSDTest_Read_Value_Check)
{
	EXPECT_CALL(mockISSD, read(LBA_NORMAL)).WillRepeatedly(Return("0"));
	EXPECT_EQ(mockISSD.read(LBA_NORMAL), "0");
}

TEST_F(SSDTestFixture, ISSDTest_Read_Execute)
{
	EXPECT_CALL(mockISSD, read(LBA_NORMAL)).Times(1);
	//testApp->read(LBA_NORMAL);
}

TEST_F(SSDTestFixture, ISSDTest_FullRead_Success)
{
	EXPECT_CALL(mockISSD, read(_)).Times(LBA_COUNT);
	testApp->fullread();
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


TEST_F(SSDTestFixture, ISSDTest_Write_Execute) {

	EXPECT_CALL(mockISSD, write(LBA_NORMAL, DATA_NORMAL))
		.Times(1)
		;
	//testApp->write(LBA_NORMAL, DATA_NORMAL);
}

TEST_F(SSDTestFixture, ISSDTest_FullWrite_Success) {

	EXPECT_CALL(mockISSD, write(_, DATA_NORMAL))
		.Times(LBA_COUNT)
		;

	testApp->fullwrite(DATA_NORMAL);
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

	//testApp->runTestApp1();
}

TEST_F(SSDTestFixture, ISSDTest_TestApp2ReadWrite_Success) {

	EXPECT_CALL(mockISSD, write(_,_))
		.Times(186)
		;

	EXPECT_CALL(mockISSD, read(_))
		.Times(6)
		.WillRepeatedly(Return(string("0x12345678")))
		;

	//EXPECT_EQ(true, testApp->runTestApp2());
}

TEST_F(SSDTestFixture, ISSDTest_TestApp2Read_False) {

	EXPECT_CALL(mockISSD, read(_))
		.Times(2)
		.WillOnce(Return(string("0x12345678")))
		.WillOnce(Return(string("0xAAAABBBB")))
		;
	
	//EXPECT_EQ(false, testApp->runTestApp2());
}


TEST_F(VirtualSSDTestFixture, VirtualSSDTest_Compare)
{
	VirtualSSD virtualSSD;

	EXPECT_EQ(virtualSSD.execute(generateWriteCmd(LBA_NORMAL, DATA_NORMAL)), true);
	EXPECT_EQ(virtualSSD.execute(generateReadCmd(LBA_NORMAL)), true);
	EXPECT_EQ(virtualSSD.getReadData(), DATA_NORMAL);
}

TEST_F(VirtualSSDTestFixture, VirtualSSDTest_TestApp1)
{
	//EXPECT_TRUE(testApp->runTestApp1());
}

TEST_F(VirtualSSDTestFixture, VirtualSSDTest_TestApp2)
{
	//EXPECT_TRUE(testApp->runTestApp2());
}
