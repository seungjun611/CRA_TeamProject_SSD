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
	PRINTLOG("READ LBA : " + to_string(lba)+ " START!");
	if (!_ssd->READ(lba)) {
		throw std::invalid_argument("sendReadSSDCmd Failed");
	}
	else {
		std::cout << _ssd->getReadData() << std::endl;
	}
	PRINTLOG("READ LBA : " + to_string(lba) + " END!");
}