#pragma once

#include "ISSD.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

const int MIN_LBA = 0;
const int MAX_LBA = 99;

class TestApplication {
public:
	void write(int lba, string data) {
		ssd->write(lba, data);
	}

	void read(int lba) {
		ssd->read(lba);
	}

	void exit() {
		//TBD. cache 값 저장
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
			ssd->read(lba);
		}
	}

	string makeRandomDataPattern() {
		srand((unsigned int)time(NULL));
		stringstream dataStream;

		dataStream << setfill('0') << std::setw(8) << std::hex << rand() % 0xFFFFFFFF;

		return string("0x").append(dataStream.str());
	}

	void runTestApp1() {
		string writeData = makeRandomDataPattern();

		fullwrite(writeData);
		fullReadVerify(writeData);
	}

	void fullReadVerify(const std::string& writeData)
	{
		string readData;

		for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
			if ((readData = ssd->read(lba)) != writeData) {
				cout << "[FAIL] Data mismatch. Expect = " << writeData << ", Actual = " << readData << endl;
				return;
			}
		}
	}

	void set_ssd(ISSD* ssd_) {
		ssd = ssd_;
	}

	ISSD* ssd;
};
