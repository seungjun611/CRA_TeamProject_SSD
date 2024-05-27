#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "EraseCommand.h"
#include "../TestApplication.cpp"

using namespace std;

EraseCommand::EraseCommand(ISSD* ssd, const vector<string>& args) :
    _ssd{ ssd }, _args{ args }
{

}

void EraseCommand::execute()
{
    this->check();
    sendWriteSSDCmd(std::stoi(_args[1]), _args[2]);
}

void EraseCommand::check()
{
    assertInvalidNumberOfArgument(_args, "write", 3);
    assertInvalidLBA(_args[1]);
    assertInvalidDataType(_args[2]);
    assertInvalidDataLength(_args[2]);
}

void EraseCommand::sendWriteSSDCmd(int lba, string data) {
    SSDCommand cmd{ OPCODE::W, lba, data };
    if (!_ssd->execute(cmd)) {
        throw std::invalid_argument("sendWriteSSDCmd Failed");
    }
}