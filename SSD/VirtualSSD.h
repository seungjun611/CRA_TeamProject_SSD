#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "ISSD.h"

class VirtualSSD : public ISSD {
public:
	VirtualSSD();
	~VirtualSSD() override;
	bool execute(SSDCommand command) override;
	const char* getReadFileName() override;

private:
	const char* RESULT_FILE_NAME = "result.txt";
	const char* NAND_FILE_NAME = "nand.txt";
	const char* BUFFER_FILE_NAME = "buffer.txt";
	const char* INIT_VALUE = "0x00000000";
	const int ERASE_MAXSIZE = 10;
	const int CMD_BUFFER_SIZE = 10;

	std::map<int, std::string> cache;	
	std::vector<SSDCommand> cmdBuffer;

	void write(int lba, std::string data) override;
	std::string read(int lba) override;
	bool erase(int lba, int size);
	bool flush();

	void executeGC();
	std::vector<SSDCommand> remakeCommand(std::vector<std::string>& validBitmap);
	void getLastData(std::vector<std::string>& validBitmap);
	void fetchDataFromNAND();
	bool isBufferFull();
	void executeBufferCmd();
	void flushToNAND();
	std::string readCache(int lba);
	void writeFile(const std::string fileName, const std::vector<std::string> data);
	std::vector<std::string> cmd_buffer_to_string(std::vector<SSDCommand> cmds);
};