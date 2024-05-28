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
#include "../SSD/VirtualSSD.cpp"
#include "../SSD/ISSD.h"
#include "../CRA_TeamProject_SSD/Logger.cpp"

using namespace std;
using namespace testing;

const int LBA_NORMAL = 23;
const int LBA_LESS_THAN_0 = -1;
const int LBA_OVER_THAN_99 = 100;

const string DATA_NORMAL = "0x11111111";

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

TEST_F(VirtualSSDTestFixture, VirtualSSDTest_Compare)
{
	VirtualSSD virtualSSD;

	EXPECT_EQ(virtualSSD.execute(generateWriteCmd(LBA_NORMAL, DATA_NORMAL)), true);
	EXPECT_EQ(virtualSSD.execute(generateReadCmd(LBA_NORMAL)), true);
	EXPECT_EQ(virtualSSD.getReadData(), DATA_NORMAL);
}

TEST_F(VirtualSSDTestFixture, VirtualSSDTest_TestApp1)
{
	TestApp1 testApp(&virtualSSD);
	testApp.run(vector<string>{""});
}

TEST_F(VirtualSSDTestFixture, VirtualSSDTest_TestApp2)
{
	TestApp2 testApp(&virtualSSD);
	testApp.run(vector<string>{"testapp2"});
}
