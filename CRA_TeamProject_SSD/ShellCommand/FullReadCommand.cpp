#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "FullReadCommand.h"
#include "../Application/TestApplication.h"

using namespace std;

FullReadCommand::FullReadCommand(ISSD* ssd, const vector<string>& args) :
    _ssd{ ssd }, _args{ args }
{

}

void FullReadCommand::execute()
{
    this->check();
    //_app->fullread();
}

void FullReadCommand::check()
{
    assertInvalidNumberOfArgument(_args, "fullread", 1);
}
