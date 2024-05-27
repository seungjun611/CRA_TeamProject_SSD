#include "VirtualSSD.h"

using namespace std;

void VirtualSSD::write(int lba, string data)
{
	if (cache.find(lba) != cache.end()) {
		cache.erase(lba);
	}
	cache.insert({ lba, data });
}

void VirtualSSD::erase(int lba, int size)
{
	for (int delta = 0; delta < size; delta++) {
		cache[lba + delta] = INIT_VALUE;
	}
}

void VirtualSSD::erase_range(int startLBA, int endLBA)
{
	for (int Lba = startLBA; Lba <= endLBA; Lba++) {
		cache[Lba] = INIT_VALUE;
	}
}


std::string VirtualSSD::read(int lba)
{
	string retCacheValue;
	if (cache.find(lba) == cache.end()) {
		retCacheValue = INIT_VALUE;
	}
	else {
		retCacheValue = cache[lba];
	}

	writeFile(RESULT_FILE_NAME, vector<string>{retCacheValue});
	return retCacheValue;
}

bool VirtualSSD::execute(SSDCommand command)
{
	return false;
}

VirtualSSD::~VirtualSSD()
{
	internalFlush();
}

void VirtualSSD::internalFlush()
{
	vector<string> datas;

	for (map<int, string>::iterator it = cache.begin(); it != cache.end(); it++) {
		datas.push_back(to_string((*it).first).append(",").append((*it).second).append("\n"));
	}
	writeFile(NAND_FILE_NAME, datas);
}


void VirtualSSD::writeFile(const string fileName, vector<string> datas)
{
	std::ofstream file(fileName);

	for (vector<string>::iterator it = datas.begin(); it != datas.end(); it++) {
		file << (*it);
	}
	file.close();
}

