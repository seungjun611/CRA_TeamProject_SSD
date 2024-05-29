#include <vector>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
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

	}

	SSDCommand generateReadCmd(int lba) {
		return SSDCommand{ OPCODE::R, lba, "", 0 };
	}

	SSDCommand generateWriteCmd(int lba, string data) {
		return SSDCommand{ OPCODE::W, lba, data, 0 };
	}

	VirtualSSD virtualSSD;
};

TEST_F(VirtualSSDTestFixture, VirtualSSDTest_Compare)
{
	VirtualSSD virtualSSD;

	EXPECT_EQ(virtualSSD.execute(generateWriteCmd(LBA_NORMAL, DATA_NORMAL)), true);
	EXPECT_EQ(virtualSSD.execute(generateReadCmd(LBA_NORMAL)), true);
	EXPECT_EQ(virtualSSD.getReadData(), DATA_NORMAL);
}
