#include "VirtualSSD.h"

using namespace std;

void VirtualSSD::write(int lba, string data)
{
	if (cache.find(lba) != cache.end()) {
		cache.erase(lba);
	}
	cache.insert({ lba, data });
}

std::string VirtualSSD::read(int lba)
{
	return std::string("temp");
}

VirtualSSD::~VirtualSSD()
{
	internalFlush();
}

void VirtualSSD::internalFlush()
{
	FILE* fp;
	fopen_s(&fp, NAND_FILE_NAME, "w+");

	if (fp == nullptr) {
		throw exception_ptr();
	}

	for (map<int, string>::iterator it = cache.begin(); it != cache.end(); it++) {
		string line = to_string((*it).first).append(",").append((*it).second).append("\n");
		fwrite(line.c_str(), sizeof(char), line.length(), fp);
	}
	fclose(fp);
}

