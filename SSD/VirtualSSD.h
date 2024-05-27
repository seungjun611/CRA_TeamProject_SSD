#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "ISSD.h"

class VirtualSSD : public ISSD {
public:
	const char* RESULT_FILE_NAME = "result.txt";

	VirtualSSD();
	~VirtualSSD() override;
	void write(int lba, std::string data) override;
	std::string read(int lba) override;
	bool execute(SSDCommand command) override;

private:
	const char* NAND_FILE_NAME = "nand.txt";
	const char* INIT_VALUE = "0x00000000";

	std::map<int, std::string> cache;	
	void erase(int lba, int size);
	void erase_range(int startLBA, int endLBA);

	void fetchDataFromNAND();
	bool isBufferFull();
	void internalFlush();
	void writeFile(const std::string fileName, const std::vector<std::string> data);
};