#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "WriteCommand.h"
#include "../Application/TestApplication.h"
#include "../Logger.h"
using namespace std;

WriteCommand::WriteCommand(ISSD* ssd, const vector<string>& args) :
    _ssd{ ssd }, _args{ args }
{

}

void WriteCommand::execute()
{
    this->check();
    sendWriteSSDCmd(std::stoi(_args[1]), _args[2]);
}

void WriteCommand::check()
{
    assertInvalidNumberOfArgument(_args, "write", 3);
    assertInvalidLBA(_args[1]);
    assertInvalidDataType(_args[2]);
    assertInvalidDataLength(_args[2]);
}

void WriteCommand::sendWriteSSDCmd(int lba, string data) {
    PRINTLOG("WRITE LBA : " + to_string(lba) + " DATA : " + data +  " START!");
	SSDCommand cmd{ OPCODE::W, lba, data };
	if (!_ssd->execute(cmd)) {
		throw std::invalid_argument("sendWriteSSDCmd Failed");
	}
    PRINTLOG("WRITE LBA : " + to_string(lba) + " DATA : " + data + " END!");
}