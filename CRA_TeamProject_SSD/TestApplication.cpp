#pragma once

#include "ISSD.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <random>

using namespace std;

const int MIN_LBA = 0;
const int MAX_LBA = 99;

class TestApplication {
public:
	void write(int lba, string data) {
		ssd->write(lba, data);
	}

	void read(int lba) {
		cout << ssd->read(lba) << endl;
	}

	void help() {
		std::cout << "************************************" << std::endl;
		std::cout << "************COMMAND HELP************" << std::endl;
		std::cout << "************************************" << std::endl;
		std::cout << "*** [ShellProgram commands help] ***" << std::endl;
		std::cout << "** write: write to SSD / usage: write <LBA> <VALUE>" << std::endl;
		std::cout << "** read: read from SSD / usage: read <LBA>" << std::endl;
		std::cout << "** exit: exit program / usage: exit" << std::endl;
		std::cout << "** help: help command" << std::endl;
		std::cout << "** fullwrite: write at all LBAs / usage: fullwrite <VALUE>" << std::endl;
		std::cout << "** fullread: read all LBAs / usage: fullread" << std::endl;
		std::cout << "** testapp1: After fullwrite, check if fullread value is corrrect according to the written value." << std::endl;
		std::cout << "** testapp2: After overwrite, read the LBA value to make sure LBA value is correct according to overwriten value" << std::endl;
		std::cout << "** LBA range: 0 ~ 99" << std::endl;
		std::cout << "** VALUE range: 0x00000000 ~ 0xFFFFFFFF" << std::endl;
		std::cout << "***********************************" << std::endl;
		std::cout << std::endl;
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

	string makeRandomDataPattern() {
		random_device rd;
		stringstream dataStream;

		dataStream.setf(ios::uppercase);
		dataStream << setfill('0') << std::setw(8) << std::hex << rd() % 0xFFFFFFFF;

		return string("0x").append(dataStream.str());
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

	bool runTestApp1() {
		string writeData = makeRandomDataPattern();

		fullwrite(writeData);
		if (!readVerify(MIN_LBA, MAX_LBA, writeData)) {
			return false;
		}

		cout << "[SUCCESS]" << endl;
		return true;
	}

	bool runTestApp2()
	{
		vector<int> lbas = { 0,1,2,3,4,5 };

		setLbaRepeatly(lbas, "AAAABBBB", 30);
		setLbaRepeatly(lbas, "12345678", 1);

		if (!readVerify(lbas.front(), lbas.back(), "12345678")) {
			return false;
		}

		cout << "[SUCCESS]" << endl;
		return true;
	}

	void set_ssd(ISSD* ssd_) {
		ssd = ssd_;
	}

	~TestApplication() {
		if (ssd != nullptr) {
			ssd->~ISSD();
		}
	}

	ISSD* ssd;
};
