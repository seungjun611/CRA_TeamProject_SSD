#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "EraseRangeCommand.h"
#include "../TestApplication.cpp"

using namespace std;

EraseRangeCommand::EraseRangeCommand(ISSD* ssd, const vector<string>& args) :
    _ssd{ ssd }, _args{ args }
{

}

void EraseRangeCommand::execute()
{
    this->check();
    sendEraseRangeSSDCmd(std::stoi(_args[1]), std::stoi(_args[2]));
}

void EraseRangeCommand::check()
{
    assertInvalidNumberOfArgument(_args, "erase_range", 3);
}

void EraseRangeCommand::sendEraseRangeSSDCmd(int start_lba, int end_lba) {
    int size = end_lba - start_lba;
    SSDCommand cmd{ OPCODE::E, start_lba, "",  size};
    if (!_ssd->execute(cmd)) {
        throw std::invalid_argument("sendEraseRangeSSDCmd Failed");
    }
}