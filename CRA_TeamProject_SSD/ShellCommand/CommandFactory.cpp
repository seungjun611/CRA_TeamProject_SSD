#pragma once
#include <string>
#include "CommandFactory.h"
#include "ICommand.h"
#include "WriteCommand.h"
#include "ReadCommand.h"
#include "ExitCommand.h"

using namespace std;

CommandFactory::CommandFactory(TestApplication* app) : _app{ app } {}

ICommand* CommandFactory::getCommand(const vector<string>& args)
{
	ICommand* command = nullptr;

	if (args[0] == "write") {
		command = new WriteCommand(_app, args);
	}
	else if (args[0] == "read") {
		command = new ReadCommand(_app, args);
	}
	else if (args[0] == "exit") {
		command = new ExitCommand(args);
	}

	return command;
}