﻿#pragma once
#include "ICommand.h"
#include <string>
#include <vector>
using namespace std;

class TestApplication;

class WriteCommand : public ICommand
{
public:
	WriteCommand(TestApplication* app, const vector<string>& args);

	void execute();
	void check();

private:
	TestApplication* _app;
	vector<string> _args;

};