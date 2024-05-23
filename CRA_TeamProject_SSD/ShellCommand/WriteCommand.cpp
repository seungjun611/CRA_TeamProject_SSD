#pragma once
#include "ICommand.h"
#include "WriteCommand.h"
#include "../TestApplication.cpp"

using namespace std;

WriteCommand::WriteCommand(TestApplication* app, const vector<string>& args) :
    _app{ app }, _args{ args }
{

}

void WriteCommand::execute()
{
    this->check();
	_app->write(std::stoi(_args[1]), _args[2]);
}

void WriteCommand::check()
{
    assertInvalidNumberOfArgument(_args, "write", 3);

    int lba = std::stoi(_args[1]);
    if (lba < 0 || lba > 100) {
        throw std::invalid_argument("lba 값은 0 이상 100 미만이어야 한다");
    }

    if (_args[2][0] != '0' || _args[2][1] != 'x') {
        throw std::invalid_argument("data type 은 hex 여야 한다");
    }

    if (_args[2].size() != 10) {
        throw std::invalid_argument("data 의 자리수는 8이어야 한다");
    }
}
