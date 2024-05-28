#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "FullWriteCommand.h"
#include "../Application/TestApplication.h"
#include "../Logger.h"
using namespace std;

FullWriteCommand::FullWriteCommand(ISSD* ssd, const vector<string>& args) :
    _ssd{ ssd }, _args{ args }
{

}

void FullWriteCommand::execute()
{
    this->check();
    sendFullWriteSSDCmd(_args[1]);
}

void FullWriteCommand::check()
{
    assertInvalidNumberOfArgument(_args, "fullwrite", 2);

    if (_args[1][0] != '0' || _args[1][1] != 'x') {
        throw std::invalid_argument("data type 은 hex 여야 한다");
    }

    if (_args[1].size() != 10) {
        throw std::invalid_argument("data 의 자리수는 8이어야 한다");
    }
}

void FullWriteCommand::sendFullWriteSSDCmd(string data) {
    PRINTLOG("FULL WRITE " + to_string(_ssd->getMinLBA()) + " ~ " + to_string(_ssd->getMaxLBA()) + " DATA : " + data +" START!");
    for (int lba = _ssd->getMinLBA(); lba <= _ssd->getMaxLBA(); lba++) {
        if (!_ssd->WRITE(lba, data)) {
            PRINTLOG("sendWriteSSDCmd FAIL!");
            throw std::invalid_argument("sendWriteSSDCmd Failed");
        }
    }
    PRINTLOG("FULL WRITE " + to_string(_ssd->getMinLBA()) + " ~ " + to_string(_ssd->getMaxLBA()) + " DATA : " + data + " END!");
}
