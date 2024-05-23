#pragma once
#include <string>
#include "ICommand.h"
#include "WriteCommand.h"

using namespace std;

class CommandFactory
{
public:
	CommandFactory(TestApplication* app) : _app{ app } {}
	ICommand* getCommand(const vector<string>& args);

private:
	TestApplication* _app;
};

ICommand* CommandFactory::getCommand(const vector<string>& args)
{
	ICommand* command = nullptr;

	if (args[0] == "write") {
		command = new WriteCommand(_app, args);
	}

	return command;
}

