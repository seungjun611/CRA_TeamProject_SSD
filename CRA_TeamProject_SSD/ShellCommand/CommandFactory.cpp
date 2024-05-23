#pragma once
#include <string>
#include <stdexcept>
#include "CommandFactory.h"
#include "../IApplication.h"
#include "ICommand.h"
#include "WriteCommand.h"
#include "ReadCommand.h"
#include "ExitCommand.h"
#include "HelpCommand.h"
#include "FullWriteCommand.h"
#include "FullReadCommand.h"
#include "TestApp1Command.h"
#include "TestApp2Command.h"

using namespace std;

CommandFactory::CommandFactory(IApplication* app) : _app{ app } {}

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
	else if (args[0] == "help") {
		command = new HelpCommand(_app, args);
	}
	else if (args[0] == "fullwrite") {
		command = new FullWriteCommand(_app, args);
	}
	else if (args[0] == "fullread") {
		command = new FullReadCommand(_app, args);
	}
	else if (args[0] == "testapp1") {
		command = new TestApp1Command(_app, args);
	}
	else if (args[0] == "testapp2") {
		command = new TestApp2Command(_app, args);
	}
	else
	{
		throw std::invalid_argument("지원하지 않는 command 이다");
	}

	return command;
}