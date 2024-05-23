#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "HelpCommand.h"
#include "../TestApplication.cpp"

using namespace std;

HelpCommand::HelpCommand(IApplication* app, const vector<string>& args) :
    _app{ app }, _args{ args }
{

}

void HelpCommand::execute()
{
    this->check();
    _app->help();
}

void HelpCommand::check()
{
    assertInvalidNumberOfArgument(_args, "help", 1);
}
