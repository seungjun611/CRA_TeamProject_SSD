#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "FlushCommand.h"
#include "../Application/TestApplication.h"
#include "../Logger.h"

using namespace std;

FlushCommand::FlushCommand(ISSD* ssd, const vector<string>& args) :
    _ssd{ ssd }, _args{ args }
{

}

void FlushCommand::execute()
{
    this->check();
	sendFlushSSDCmd();
}

void FlushCommand::check()
{
    assertInvalidNumberOfArgument(_args, "flush", 1);
}

void FlushCommand::sendFlushSSDCmd() {
	PRINTLOG("FLUSH START!");
	SSDCommand cmd{ OPCODE::F};
	if (!_ssd->execute(cmd)) {
		throw std::invalid_argument("sendFlushSSDCmd  Failed");
	}
	PRINTLOG("FLUSH END!");
}