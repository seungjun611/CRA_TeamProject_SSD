#include "VirtualSSD.h"

using namespace std;

bool VirtualSSD::execute(SSDCommand command)
{
	try {
		if (command.opcode == OPCODE::W || command.opcode == OPCODE::E) {
			cmdBuffer.push_back(command);
			if (isBufferFull()) {
				if (!flush()) {
					return false;
				}
			}
		}
		else if (command.opcode == OPCODE::R) {
			read(command.param1);
		}
		else if (command.opcode == OPCODE::F) {
			if (!flush()) {
				return false;
			}
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

bool VirtualSSD::erase(int lba, int size)
{
	if (size > ERASE_MAXSIZE) {
		return false;
	}

	for (int currentLba = lba; currentLba < lba + size; currentLba++) {
		if (cache.find(currentLba) == cache.end())
			continue;
		cache.erase(currentLba);
	}
	return true;
}

bool VirtualSSD::erase_range(int startLBA, int endLBA)
{
	return erase(startLBA, endLBA - startLBA);
}

bool VirtualSSD::flush()
{
	try {
		executeGC();

		for (SSDCommand command : cmdBuffer) {
			if (command.opcode == OPCODE::W) {
				write(command.param1, command.param2);
			}
			else if (command.opcode == OPCODE::E) {
				erase(command.param1, command.param3);
			}
			else {
				throw exception("Invalid opcode");
			}
		}
		cmdBuffer.clear();
	}
	catch (exception e) {
		return false;
	}

	return true;
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
	minLBA = 0;
	maxLBA = 99;
	fetchDataFromNAND();
}

VirtualSSD::~VirtualSSD()
{
	internalFlush();
}

void VirtualSSD::executeGC()
{
	string validData[100] = { "", };

	if (maxLBA - minLBA < 0) {
		return;
	}

	/*validBitmap = (char**)malloc(sizeof(char*) * (maxLBA - minLBA + 1));
	for (int idx = 0; idx < maxLBA - minLBA + 1; idx++) {
		validBitmap[idx] = { 0, };
	}*/

	getLastestData(validData);
	cmdBuffer = remakeCommand(validData);
	//free(validBitmap);
}

vector<SSDCommand> VirtualSSD::remakeCommand(std::string* validData)
{
	vector<SSDCommand> result;
	SSDCommand candidateCommand{};
	int size = 0;

	for (int idx = minLBA; idx < maxLBA - minLBA + 1; idx++) {
		size++;
		if (validData[idx] == "" && candidateCommand.opcode != OPCODE::E) continue;

		if (validData[idx] == INIT_VALUE) {
			if (idx == validData->size() - 1) {
				candidateCommand.param3 = size;
				result.push_back(candidateCommand);
			}
			if (candidateCommand.opcode == OPCODE::E) continue;
			candidateCommand.opcode = OPCODE::E;
			candidateCommand.param1 = idx;
			candidateCommand.param2 = "";
			size = 0;
			continue;
		}
		else {
			if (candidateCommand.opcode == OPCODE::E) {
				candidateCommand.param3 = size;
				result.push_back(candidateCommand);
				memset(&candidateCommand, 0x0, sizeof(SSDCommand));
			}
			if (validData[idx] == "") continue;
			candidateCommand.opcode = OPCODE::W;
			candidateCommand.param1 = idx;
			candidateCommand.param2 = string(validData[idx]);
			result.push_back(candidateCommand);
		}
		memset(&candidateCommand, 0x0, sizeof(SSDCommand));
	}
	if (candidateCommand.opcode == OPCODE::E) {
		candidateCommand.param3 = size;
		result.push_back(candidateCommand);
	}

	return result;
}

void VirtualSSD::getLastestData(string* validData)
{
	for (vector<SSDCommand>::reverse_iterator it = cmdBuffer.rbegin(); it != cmdBuffer.rend(); it++) {
		SSDCommand cmd = *it;
		switch (cmd.opcode)
		{
		case OPCODE::W:
			if (validData[cmd.param1] == "") {
				validData[cmd.param1] = cmd.param2;
			}
			break;
		case OPCODE::E:
			for (int lba = cmd.param1; lba < cmd.param3; lba++) {
				if (validData[lba] == "") {
					validData[lba] = INIT_VALUE;
				}
			}
			break;
		default:
			break;
		}
	}
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
	return (cmdBuffer.size() > 9) ? true : false;
}

void VirtualSSD::internalFlush()
{
	vector<string> datas;

	flush();

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

