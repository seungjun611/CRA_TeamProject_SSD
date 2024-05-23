#pragma once
#include <string>
#include <map>
#include <fstream>
#include "ISSD.h"

class VirtualSSD : public ISSD {
public:
	~VirtualSSD();
	void write(int lba, std::string data) override;
	std::string read(int lba) override;

private:
	const char* NAND_FILE_NAME = "nand.txt";
	const char* RESULT_FILE_NAME = "result.txt";
	const char* INIT_VALUE = "0x00000000";

	std::map<int, std::string> cache;

	void internalFlush();
	void writeFile(const std::string fileName, const std::string data);
};