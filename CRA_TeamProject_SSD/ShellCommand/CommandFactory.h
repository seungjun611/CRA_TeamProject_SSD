#pragma once
#include <string>
#include "ICommand.h"
#include "WriteCommand.h"
#include "../../SSD/ISSD.h"

using namespace std;

class IApplication;

class CommandFactory
{
public:
	static CommandFactory* getInstance(ISSD* ssd);
	static void resetInstance();
	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;
	ICommand* getCommand(const vector<string>& args);

private:
	CommandFactory(ISSD* ssd);
	static CommandFactory* _instance;
	ISSD* _ssd;
};
