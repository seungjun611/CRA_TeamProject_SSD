#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include "../ShellCommand/ICommand.h"
#include "FullRead10AndCompare.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>

using namespace std;

FullRead10AndCompare::FullRead10AndCompare(ISSD* ssd) : ssd{ ssd } {
	MIN_LBA = ssd->getMinLBA();
	MAX_LBA = ssd->getMaxLBA();
}

void FullRead10AndCompare::fullwrite(string data) {
	for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
		ssd->WRITE(lba, data);
	}
}

bool FullRead10AndCompare::readVerify(const int startLBA, const int endLBA, const std::string& writeData)
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

string FullRead10AndCompare::makeRandomDataPattern() {
	random_device rd;
	stringstream dataStream;

	dataStream.setf(ios::uppercase);
	dataStream << setfill('0') << std::setw(8) << std::hex << rd() % 0xFFFFFFFF;

	return string("0x").append(dataStream.str());
}

bool FullRead10AndCompare::run(const std::vector<std::string>& args)
{
	string writeData = makeRandomDataPattern();

	fullwrite(writeData);

	for (int i = 0; i < 10; i++)
	{
		if (!readVerify(MIN_LBA, MAX_LBA, writeData)) {
			return false;
		}
	}

	return true;
}
