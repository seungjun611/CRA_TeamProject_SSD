#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "EraseRangeCommand.h"
#include "../Application/TestApplication.h"
#include "../Logger.h"

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
    PRINTLOG("ERASE "+to_string(start_lba) + " ~ " + to_string(end_lba - 1) + " START!");
    int size = end_lba - start_lba;
    if (!_ssd->ERASE(start_lba, size)) {
        throw std::invalid_argument("sendEraseRangeSSDCmd Failed");
    }
    PRINTLOG("ERASE " + to_string(start_lba) + " ~ " + to_string(end_lba - 1) +" END!");
}