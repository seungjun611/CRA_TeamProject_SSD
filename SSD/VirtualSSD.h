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
	const int ERASE_MAXSIZE = 10;

	std::map<int, std::string> cache;	
	std::vector<SSDCommand> cmdBuffer;

	bool erase(int lba, int size);
	bool erase_range(int startLBA, int endLBA);
	bool flush();

	void executeGC();
	std::vector<SSDCommand> remakeCommand(std::string* validBitmap);
	void getLastData(std::string* validBitmap);
	void fetchDataFromNAND();
	bool isBufferFull();
	void internalFlush();
	void writeFile(const std::string fileName, const std::vector<std::string> data);
};