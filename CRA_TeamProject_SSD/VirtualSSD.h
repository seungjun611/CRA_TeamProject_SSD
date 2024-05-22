#pragma once
#include <string>
#include <map>
#include "ISSD.h"

class VirtualSSD : public ISSD {
public:
	void write(int lba, int data) override;
	std::string read(int lba) override;
	~VirtualSSD();

private:
	const char* NAND_FILE_NAME = "nand.txt";
	std::map<int, int> cache;
	void internalFlush();
};