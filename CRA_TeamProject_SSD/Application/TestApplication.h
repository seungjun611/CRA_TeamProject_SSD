﻿#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <random>

using namespace std;

class TestApplication : public IApplication
{
public:
	TestApplication(ISSD* ssd) : ssd{ ssd } {
		MIN_LBA = ssd->getMinLBA();
		MAX_LBA = ssd->getMaxLBA();
	}

	bool run() override
	{
		return true;
	}

	void fullwrite(string data) {
		for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
			ssd->write(lba, data);
		}
	}

	void fullread() {
		for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
			cout << ssd->read(lba) << endl;
		}
	}

	bool readVerify(const int startLBA, const int endLBA, const std::string& writeData)
	{
		string readData;

		for (int lba = startLBA; lba <= endLBA; lba++) {
			if ((readData = ssd->read(lba)) != writeData) {
				cout << "[FAIL] LBA" << lba << " Data mismatch.Expect = " << writeData << ", Actual = " << readData << endl;
				return false;
			}
		}

		return true;
	}

	void setLbaRepeatly(const std::vector<int> lbas, const string value, const int repeat)
	{
		int cnt = 0;
		do {
			for (auto lba : lbas) {
				ssd->write(lba, value);
			}
		} while (++cnt < repeat);
	}

	bool runTestApp2()
	{
		vector<int> lbas = { 0,1,2,3,4,5 };

		setLbaRepeatly(lbas, "0xAAAABBBB", 30);
		setLbaRepeatly(lbas, "0x12345678", 1);

		if (!readVerify(lbas.front(), lbas.back(), "0x12345678")) {
			return false;
		}

		cout << "[SUCCESS]" << endl;
		return true;
	}

	void set_ssd(ISSD* ssd_) {
		ssd = ssd_;
	}

	ISSD* ssd;
	int MIN_LBA;
	int MAX_LBA;
};
