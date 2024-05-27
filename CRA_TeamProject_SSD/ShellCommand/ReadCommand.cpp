#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "ReadCommand.h"
#include "../Application/TestApplication.h"
#include "../Logger.h"

using namespace std;

ReadCommand::ReadCommand(ISSD* ssd, const vector<string>& args) :
    _ssd{ ssd }, _args{ args }
{

}

void ReadCommand::execute()
{
    this->check();
	sendReadSSDCmd(std::stoi(_args[1]));
}

void ReadCommand::check()
{
    assertInvalidNumberOfArgument(_args, "read", 2);
    assertInvalidLBA(_args[1]);
}

void ReadCommand::sendReadSSDCmd(int lba) {
	SSDCommand cmd{ OPCODE::R, lba };
	PRINTLOG("READ LBA : " + to_string(lba)+ " START!");
	if (!_ssd->execute(cmd)) {
		throw std::invalid_argument("sendReadSSDCmd Failed");
	}
	else {
		string filename = "result.txt";
		std::ifstream file(filename);
		if (!file) {
			PRINTLOG(filename + " OPEN FAIL!");
			std::cerr << "Failed to open file: " << filename << std::endl;
			return;
		}
		std::string line;
		while (std::getline(file, line)) {
			std::cout << line << std::endl;
		}
		file.close();
	}
	PRINTLOG("READ LBA : " + to_string(lba) + " END!");
}