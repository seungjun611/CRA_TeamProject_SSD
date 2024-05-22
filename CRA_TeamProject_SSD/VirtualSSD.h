#pragma once
#include <string>
#include <map>
#include "ISSD.h"

class VirtualSSD : public ISSD {
public:
	~VirtualSSD();
	void write(int lba, std::string data) override;
	std::string read(int lba) override;

private:
	const char* NAND_FILE_NAME = "nand.txt";
	std::map<int, std::string> cache;

	void internalFlush();
};