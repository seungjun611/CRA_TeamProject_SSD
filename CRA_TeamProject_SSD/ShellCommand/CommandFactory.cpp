﻿#pragma once
#include <string>
#include <stdexcept>
#include "CommandFactory.h"
#include "../IApplication.h"
#include "ICommand.h"
#include "WriteCommand.h"
#include "ReadCommand.h"
#include "ExitCommand.h"
#include "HelpCommand.h"
#include "EraseSizeCommand.h"
#include "EraseRangeCommand.h"
#include "FlushCommand.h"
#include "FullWriteCommand.h"
#include "FullReadCommand.h"

using namespace std;

CommandFactory* CommandFactory::_instance = nullptr;

CommandFactory::CommandFactory(ISSD* ssd) : _ssd{ ssd } {}

CommandFactory* CommandFactory::getInstance(ISSD* ssd) {
	if (_instance == nullptr)
	{
		_instance = new CommandFactory(ssd);
	}
	return _instance;
}

void CommandFactory::resetInstance()
{
	delete _instance;
	_instance = nullptr;
}

ICommand* CommandFactory::getCommand(const vector<string>& args)
{
	ICommand* command = nullptr;

	if (args.empty()) {
		throw std::invalid_argument("아무런 명령어도 입력하지 않았습니다.");
	}

	if (args[0] == "write") {
		command = new WriteCommand(_ssd, args);
	}
	else if (args[0] == "read") {
		command = new ReadCommand(_ssd, args);
	}
	else if (args[0] == "exit") {
		command = new ExitCommand(args);
	}
	else if (args[0] == "help") {
		command = new HelpCommand(_ssd, args);
	}
	else if (args[0] == "fullwrite") {
		command = new FullWriteCommand(_ssd, args);
	}
	else if (args[0] == "fullread") {
		command = new FullReadCommand(_ssd, args);
	}
	else if (args[0] == "erase") {
		command = new EraseSizeCommand(_ssd, args);
	}
	else if (args[0] == "erase_range") {
		command = new EraseRangeCommand(_ssd, args);
	}
	else if (args[0] == "flush") {
		command = new FlushCommand(_ssd, args);
	}
	else
	{
		throw std::invalid_argument("지원하지 않는 command 이다");
	}

	return command;
}