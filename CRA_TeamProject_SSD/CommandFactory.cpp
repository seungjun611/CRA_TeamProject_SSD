#pragma once
#include <string>
#include "CommandFactory.h"
#include "ICommand.h"
#include "WriteCommand.h"

using namespace std;

CommandFactory::CommandFactory(TestApplication* app) : _app{ app } {}

ICommand* CommandFactory::getCommand(const vector<string>& args)
{
	ICommand* command = nullptr;

	if (args[0] == "write") {
		command = new WriteCommand(_app, args);
	}

	return command;
}