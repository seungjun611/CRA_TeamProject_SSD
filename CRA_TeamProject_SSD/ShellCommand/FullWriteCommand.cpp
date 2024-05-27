#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "FullWriteCommand.h"
#include "../Application/TestApplication.h"

using namespace std;

FullWriteCommand::FullWriteCommand(ISSD* ssd, const vector<string>& args) :
    _ssd{ ssd }, _args{ args }
{

}

void FullWriteCommand::execute()
{
    this->check();
    //_app->fullwrite(_args[1]);
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
