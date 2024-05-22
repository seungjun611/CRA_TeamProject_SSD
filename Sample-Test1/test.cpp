#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../CRA_TeamProject_SSD/SSD.h"

using namespace std;
using namespace testing;

class MockSSD : public SSD {
	MOCK_METHOD(void, write, (int lba, string data), (override));
	MOCK_METHOD(string, read, (int lba), (override));
};

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}