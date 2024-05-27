#pragma once
#include "ICommand.h"
#include <string>
#include <vector>
using namespace std;

class IApplication;

class HelpCommand : public ICommand
{
public:
	HelpCommand(ISSD* ssd, const vector<string>& args);

	void execute();
	void check();

private:
	ISSD* _ssd;
	vector<string> _args;
};