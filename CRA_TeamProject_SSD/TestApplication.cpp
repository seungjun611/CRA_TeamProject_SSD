#pragma once

#include "ISSD.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <stdexcept>

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

	string makeRandomDataPattern() {
		srand((unsigned int)time(NULL));
		stringstream dataStream;

		dataStream << setfill('0') << std::setw(8) << std::hex << rand() % 0xFFFFFFFF;

		return string("0x").append(dataStream.str());
	}

	bool runTestApp1() {
		string writeData = makeRandomDataPattern();

		fullwrite(writeData);
		if (!fullReadVerify(writeData)) {
			return false;
		}

		return true;
	}

	bool fullReadVerify(const std::string& writeData)
	{
		string readData;

		for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
			if ((readData = ssd->read(lba)) != writeData) {
				cout << "[FAIL] Data mismatch. Expect = " << writeData << ", Actual = " << readData << endl;
				return false;
			}
		}

		return true;
	}

	void set_ssd(ISSD* ssd_) {
		ssd = ssd_;
	}

	void setLbaRepeatly(const std::vector<int> lbas, const string value, const int repeat)
	{
		int cnt = 0;
		do {
			for (auto lba : lbas) {
				ssd->write(lba, value);
			}
		} while (cnt++ < repeat);
	}
	bool runTestApp2()
	{
		vector<int> lbas = { 0,1,2,3,4,5 };
		setLbaRepeatly(lbas, "0xAAAABBBB", 30);
		setLbaRepeatly(lbas, "0x12345678", 1);
		for (int i = 0; i < lbas.size(); i++)
		{
			string readData = getLba(i);
			if (readData != "0x12345678") {
				cout << "[FAIL] Data mismatch. Expect = " << "0x12345678" << ", Actual = " << readData << endl;
				return false;
			}
		}

		cout << "[SUCCESS]" << endl;
		return true;
	}

	string getLba(const int lba)
	{
		ssd->read(lba);
		string value = readFile("result.txt");
		return value;
	}

	string readFile(const string fileName) {
		std::ifstream file(fileName);
		if (!file.is_open()) {
			throw exception("파일을 열 수 없습니다.");
		}
		std::string line;
		std::getline(file, line);
		file.close();
		return line;
	}

	ISSD* ssd;
};
