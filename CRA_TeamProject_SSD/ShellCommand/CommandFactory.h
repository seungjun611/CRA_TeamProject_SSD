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
	CommandFactory(ISSD* ssd);
	ICommand* getCommand(const vector<string>& args);

private:
	ISSD* _ssd;
};
