#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include "../ShellCommand/ICommand.h"
#include "TestApp2.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>

using namespace std;

TestApp2::TestApp2(ISSD* ssd) : ssd{ ssd } {
	MIN_LBA = ssd->getMinLBA();
	MAX_LBA = ssd->getMaxLBA();
}

void TestApp2::setLbaRepeatly(const std::vector<int> lbas, const string value, const int repeat)
{
	int cnt = 0;
	do {
		for (auto lba : lbas) {
			ssd->WRITE(lba, value);
		}
	} while (++cnt < repeat);
}

bool TestApp2::readVerify(const int startLBA, const int endLBA, const std::string& writeData)
{
	string readData;

	for (int lba = startLBA; lba <= endLBA; lba++) {
		ssd->READ(lba);
		if ((readData = ssd->getReadData()) != writeData) {
			cout << "[FAIL] LBA" << lba << " Data mismatch.Expect = " << writeData << ", Actual = " << readData << endl;
			return false;
		}
	}

	return true;
}

bool TestApp2::run(const std::vector<std::string>& args) {
	ICommand::assertInvalidNumberOfArgument(args, "testapp2", 1);

	vector<int> lbas = { 0,1,2,3,4,5 };

	setLbaRepeatly(lbas, "0xAAAABBBB", 30);
	setLbaRepeatly(lbas, "0x12345678", 1);

	if (!readVerify(lbas.front(), lbas.back(), "0x12345678")) {
		return false;
	}

	cout << "[SUCCESS]" << endl;
	return true;
}
