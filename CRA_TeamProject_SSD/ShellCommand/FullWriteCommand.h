#pragma once
#include "ICommand.h"
#include <string>
#include <vector>
using namespace std;

class IApplication;

class FullWriteCommand : public ICommand
{
public:
	FullWriteCommand(IApplication* app, const vector<string>& args);

	void execute();
	void check();

private:
	IApplication* _app;
	vector<string> _args;
};
