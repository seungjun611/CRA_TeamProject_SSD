#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include "../ShellCommand/ICommand.h"
#include "Loop_WriteAndReadCompare.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>
#include "../Logger.h"

using namespace std;

Loop_WriteAndReadCompare::Loop_WriteAndReadCompare(ISSD* ssd) : ssd{ ssd } {
	MIN_LBA = ssd->getMinLBA();
	MAX_LBA = ssd->getMaxLBA();
}

void Loop_WriteAndReadCompare::fullwrite(string data) {
	for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
		ssd->WRITE(lba, data);
	}
}

bool Loop_WriteAndReadCompare::readVerify(const int startLBA, const int endLBA, const std::string& writeData)
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

string Loop_WriteAndReadCompare::makeRandomDataPattern() {
	random_device rd;
	stringstream dataStream;

	dataStream.setf(ios::uppercase);
	dataStream << setfill('0') << std::setw(8) << std::hex << rd() % 0xFFFFFFFF;

	return string("0x").append(dataStream.str());
}

bool Loop_WriteAndReadCompare::run(const std::vector<std::string>& args)
{
	for (int i = 0; i < 10; i++)
	{
		PRINTLOG("#"+to_string(i)+" [Step 1] MAKE RANDOM PATTERN");
		string writeData = makeRandomDataPattern();
		PRINTLOG("#" + to_string(i) + " [Step 2] FULL WRITE (PATTERN = " + writeData + ")");
		fullwrite(writeData);
		PRINTLOG("#" + to_string(i) + " [Step 3] READ VERIFY");
		if (!readVerify(MIN_LBA, MAX_LBA, writeData))
		{
			return false;
		}
	}

	return true;
}
