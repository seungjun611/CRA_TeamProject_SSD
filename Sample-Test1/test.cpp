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
#include "../CRA_TeamProject_SSD/Application/Write10AndCompare.cpp"
#include "../CRA_TeamProject_SSD/Application/Loop_WriteAndReadCompare.cpp"
#include "../CRA_TeamProject_SSD/Application/AlwaysFail.cpp"
#include "../CRA_TeamProject_SSD/Application/Runner.cpp"
#include "../CRA_TeamProject_SSD/Application/TestApplication.h"
#include "../SSD/ISSD.h"
#include "../CRA_TeamProject_SSD/Logger.cpp"

using namespace std;
using namespace testing;

class SuppressOutput {
public:
	SuppressOutput() {		
		original_cout_buffer = cout.rdbuf();
		temp_cout_buffer.open("/dev/null");
		cout.rdbuf(temp_cout_buffer.rdbuf());
	}

	~SuppressOutput() {
		cout.rdbuf(original_cout_buffer);
		temp_cout_buffer.close();
	}

private:
	streambuf* original_cout_buffer;
	ofstream temp_cout_buffer;
};

class MockISSD : public ISSD {
public:
	MockISSD() {
		ISSD::minLBA = 0;
		ISSD::maxLBA = 99;
	}
	~MockISSD() override {}
	MOCK_METHOD(void, write, (int lba, string data), (override));
	MOCK_METHOD(string, read, (int lba), (override));
	MOCK_METHOD(string, getReadData, (), (override));
	MOCK_METHOD(bool, erase, (int lba, int size), (override));
	MOCK_METHOD(bool, flush, (), (override));
	MOCK_METHOD(const char*, getReadFileName, (), (override));
	bool execute(SSDCommand command) override {
		switch (command.opcode)
		{
		case OPCODE::W:
			write(command.param1, command.param2);
			return true;
			break;
		case OPCODE::R:
			read(command.param1);
			return true;
		case OPCODE::E:
			if (erase(command.param1, command.param3)) return true;
			break;
		case OPCODE::F:
			if (flush()) return true;
			break;
		default:
			break;
		}

		return false;
	}
};

class SSDTestFixture : public Test {
public:
	void SetUp() override {
		suppressor = new SuppressOutput();

		testApp = new TestApplication(&mockISSD);
		testShell = new TestShell(&mockISSD);
	}

	void TearDown() override {
		delete suppressor;
		CommandFactory::resetInstance();
		ApplicationFactory::resetInstance();
	}

	SuppressOutput* suppressor;

	NiceMock<MockISSD> mockISSD;
	TestApplication* testApp;
	TestShell* testShell;

	void assertIllegalArgument(string command) {
		TestShell testShell(&mockISSD);
		try {
			testShell.run(command);
			FAIL();
		}
		catch (exception e) {

		}
	}

	const int LBA_COUNT = mockISSD.getMaxLBA() - mockISSD.getMinLBA() + 1;

	const int LBA_NORMAL = 23;
	const int LBA_LESS_THAN_0 = -1;
	const int LBA_OVER_THAN_99 = 100;

	const int TESTAPP2_LBA_COUNT = 6;
	const int TESTAPP2_WRITE_COUNT = 30;
	const int TESTAPP2_OVERWRITE_COUNT = 1;

	const string DATA_NORMAL = "0x11111111";
	const string TESTAPP2_DATA_NORMAL = "0x12345678";
	const string TESTAPP2_DATA_ABNORMAL = "0xAAAABBBB";
};

TEST_F(SSDTestFixture, ISSDTest_Read_Value_Check)
{
	EXPECT_CALL(mockISSD, read(LBA_NORMAL))
		.WillRepeatedly(Return(DATA_NORMAL));

	EXPECT_EQ(mockISSD.read(LBA_NORMAL), DATA_NORMAL);
}

TEST_F(SSDTestFixture, ISSDTest_Read_Execute)
{
	EXPECT_CALL(mockISSD, read(LBA_NORMAL))
		.Times(1);

	testApp->ssd->READ(LBA_NORMAL);
}

TEST_F(SSDTestFixture, ISSDTest_FullRead_Success)
{
	EXPECT_CALL(mockISSD, read(_))
		.Times(LBA_COUNT)
		;

	EXPECT_CALL(mockISSD, getReadData())
		.Times(LBA_COUNT)
		.WillRepeatedly(Return(string(DATA_NORMAL)))
		;

	testApp->fullread();
}

TEST_F(SSDTestFixture, SimpleWrite)
{
	EXPECT_CALL(mockISSD, write(LBA_NORMAL, DATA_NORMAL))
    .Times(1);

	testShell->run("write " + to_string(LBA_NORMAL) + " " + DATA_NORMAL);
}


TEST_F(SSDTestFixture, SingleRead)
{
	EXPECT_CALL(mockISSD, read(LBA_NORMAL))
		.Times(1);

	EXPECT_CALL(mockISSD, getReadData())
		.WillOnce(Return(string(DATA_NORMAL)))
		;

	testShell->run("read " + to_string(LBA_NORMAL));
}


TEST_F(SSDTestFixture, ISSDTest_Write_Execute) {

	EXPECT_CALL(mockISSD, write(LBA_NORMAL, DATA_NORMAL))
		.Times(1)
		;
	testApp->ssd->WRITE(LBA_NORMAL, DATA_NORMAL);
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

	TestApp1 testApp(&mockISSD);
	testApp.run(vector<string>{});
}

TEST_F(SSDTestFixture, ISSDTest_TestApp2ReadWrite_Success) {

	EXPECT_CALL(mockISSD, write(_,_))
		.Times(TESTAPP2_LBA_COUNT*(TESTAPP2_WRITE_COUNT+TESTAPP2_OVERWRITE_COUNT))
		;

	EXPECT_CALL(mockISSD, read(_))
		.Times(TESTAPP2_LBA_COUNT)
		;

	EXPECT_CALL(mockISSD, getReadData())
		.Times(TESTAPP2_LBA_COUNT)
		.WillRepeatedly(Return(string(TESTAPP2_DATA_NORMAL)))
		;

	TestApp2 testApp(&mockISSD);
	EXPECT_EQ(true,testApp.run(vector<string>{"testapp2"}));
}

TEST_F(SSDTestFixture, ISSDTest_TestApp2Read_False) {

	EXPECT_CALL(mockISSD, read(_))
		.Times(2)
		;

	EXPECT_CALL(mockISSD, getReadData())
		.Times(2)
		.WillOnce(Return(string(TESTAPP2_DATA_NORMAL)))
		.WillOnce(Return(string(TESTAPP2_DATA_ABNORMAL)))
		;

	TestApp2 testApp(&mockISSD);
	EXPECT_EQ(false, testApp.run(vector<string>{"testapp2"}));
}

TEST_F(SSDTestFixture, VirtualSSDTest_TestApp1)
{
	TestApp1 testApp(&mockISSD);
	testApp.run(vector<string>{""});
}

TEST_F(SSDTestFixture, VirtualSSDTest_TestApp2)
{
	TestApp2 testApp(&mockISSD);
	testApp.run(vector<string>{"testapp2"});
}