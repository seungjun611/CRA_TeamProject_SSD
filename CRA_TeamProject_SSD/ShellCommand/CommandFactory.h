#pragma once
#include <string>
#include "ICommand.h"
#include "WriteCommand.h"

using namespace std;

class IApplication;

class CommandFactory
{
public:
	CommandFactory(IApplication* app);
	ICommand* getCommand(const vector<string>& args);

private:
	IApplication* _app;
};
