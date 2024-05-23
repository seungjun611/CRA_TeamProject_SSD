#pragma once
#include "ICommand.h"
#include "ReadCommand.h"
#include "TestApplication.cpp"

using namespace std;

ReadCommand::ReadCommand(TestApplication* app, const vector<string>& args) :
    _app{ app }, _args{ args }
{

}

void ReadCommand::execute()
{
    this->check();
    _app->read(std::stoi(_args[1]));
}

void ReadCommand::check()
{
    assertInvalidNumberOfArgument(_args, "read", 2);

    int lba = std::stoi(_args[1]);
    if (lba < 0 || lba > 100) {
        throw std::invalid_argument("lba 값은 0 이상 100 미만이어야 한다");
    }
}
