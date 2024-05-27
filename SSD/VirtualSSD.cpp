#include "VirtualSSD.h"

using namespace std;

bool VirtualSSD::execute(SSDCommand command)
{
	try {
		if (command.opcode == OPCODE::W) {
			write(command.param1, command.param2);
			//if (isBufferFull()) internalFlush();
		}
		else if (command.opcode == OPCODE::R) {
			read(command.param1);
		}
		else if (command.opcode == OPCODE::E) {
			if (command.param2.empty()) {
				// erase [LBA] [SIZE]
			}
			else {
				// erase_range [Start LBA] [End LBA]
			}
			//if (isBufferFull()) internalFlush();
		}
		else if (command.opcode == OPCODE::F) {
			internalFlush();
		}
		else {
			return false;
		}
	}
	catch (exception e) {
		return false;
	}

	return true;
}

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
	for (int Lba = startLBA; Lba < endLBA; Lba++) {
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

VirtualSSD::VirtualSSD()
{
	fetchDataFromNAND();
}

VirtualSSD::~VirtualSSD()
{
	internalFlush();
}

void VirtualSSD::fetchDataFromNAND()
{
	ifstream file(NAND_FILE_NAME);
	string line;
	int commaIdx;

	if (file.is_open()) {
		while (!file.eof()) {
			file >> line;
			if ((commaIdx = line.find(',')) == -1) {
				return;
			}

			try {
				cache.insert({ stoi(line.substr(0, commaIdx)), line.substr(commaIdx + 1, line.length() - commaIdx) });
			}
			catch (exception e) {
				return;
			}
		}
	}
}

bool VirtualSSD::isBufferFull()
{
	return (cache.size() > 9) ? true : false;
}

void VirtualSSD::internalFlush()
{
	vector<string> datas;

	for (map<int, string>::iterator it = cache.begin(); it != cache.end(); it++) {
		datas.push_back(to_string((*it).first).append(",").append((*it).second).append("\n"));
	}
	writeFile(NAND_FILE_NAME, datas);
	//cache.clear(); // Old data will be lost
}

void VirtualSSD::writeFile(const string fileName, vector<string> datas)
{
	std::ofstream file(fileName);

	for (vector<string>::iterator it = datas.begin(); it != datas.end(); it++) {
		file << (*it);
	}
	file.close();
}

