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
    assertInvalidLBA(_args[1]);
}
