#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "WriteCommand.h"
#include "../TestApplication.cpp"

using namespace std;

WriteCommand::WriteCommand(IApplication* app, const vector<string>& args) :
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
    assertInvalidLBA(_args[1]);
    assertInvalidDataType(_args[2]);
    assertInvalidDataLength(_args[2]);
}
