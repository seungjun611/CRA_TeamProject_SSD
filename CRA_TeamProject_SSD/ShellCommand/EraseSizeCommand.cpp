#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "EraseSizeCommand.h"
#include "../Logger.h"
using namespace std;

EraseSizeCommand::EraseSizeCommand(ISSD* ssd, const vector<string>& args) :
    _ssd{ ssd }, _args{ args }
{

}

void EraseSizeCommand::execute()
{
    this->check();
    sendEraseSizeSSDCmd(std::stoi(_args[1]), std::stoi(_args[2]));
}

void EraseSizeCommand::check()
{
    assertInvalidNumberOfArgument(_args, "erase", 3);
    assertInvalidLBA(_args[1]);
    assertMaxSize(_args[2]);
}

void EraseSizeCommand::sendEraseSizeSSDCmd(int lba, int size) {
    PRINTLOG("ERASE Start LBA : " + to_string(lba) + " Size : " + to_string(size) +" START!");
    SSDCommand cmd{ OPCODE::E, lba, "", size };
    if (!_ssd->execute(cmd)) {
        throw std::invalid_argument("sendEraseSizeSSDCmd Failed");
    }
    PRINTLOG("ERASE Start LBA : " + to_string(lba) + " Size : " + to_string(size) + " END!");
}