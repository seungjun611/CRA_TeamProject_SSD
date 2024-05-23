#pragma once
#include <string>
#include <stdexcept>
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

	if (args.empty()) {
		throw std::invalid_argument("아무런 명령어도 입력하지 않았습니다.");
	}

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