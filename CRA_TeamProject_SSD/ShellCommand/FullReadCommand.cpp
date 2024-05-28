#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "FullReadCommand.h"
#include "../Application/TestApplication.h"
#include "../Logger.h"
using namespace std;

FullReadCommand::FullReadCommand(ISSD* ssd, const vector<string>& args) :
    _ssd{ ssd }, _args{ args }
{

}

void FullReadCommand::execute()
{
    this->check();
    sendFullReadSSDCmd();

    //_app->fullread();
}

void FullReadCommand::check()
{
    assertInvalidNumberOfArgument(_args, "fullread", 1);
}

void FullReadCommand::sendFullReadSSDCmd() {
	PRINTLOG("FULL READ" + to_string(_ssd->getMinLBA()) + " ~ " + to_string(_ssd->getMaxLBA()) +" START!");
    for (int lba = _ssd->getMinLBA(); lba <= _ssd->getMaxLBA(); lba++) {
		if (!_ssd->READ(lba)) {
			throw std::invalid_argument("sendFullReadSSDCmd Failed");
		}
		else {
			string filename = _ssd->getReadFileName();
			std::ifstream file(filename);
			if (!file) {
				std::cerr << "Failed to open file: " << filename << std::endl;
				return;
			}
			std::string line;
			while (std::getline(file, line)) {
				std::cout << line << std::endl;
			}
		}
    }
	PRINTLOG("FULL READ" + to_string(_ssd->getMinLBA()) + " ~ " + to_string(_ssd->getMaxLBA()) + " END!");
}