﻿#pragma once
#include "ICommand.h"
#include <string>
#include <vector>
using namespace std;

class IApplication;

class FullWriteCommand : public ICommand
{
public:
	FullWriteCommand(ISSD* ssd, const vector<string>& args);

	void execute();
	void check();
	void sendFullWriteSSDCmd(string data);

private:
	ISSD* _ssd;
	vector<string> _args;
};
