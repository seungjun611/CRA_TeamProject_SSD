#pragma once
#include <string>
#include "ICommand.h"
#include "WriteCommand.h"

using namespace std;

class CommandFactory
{
public:
	CommandFactory(TestApplication* app);
	ICommand* getCommand(const vector<string>& args);

private:
	TestApplication* _app;
};
