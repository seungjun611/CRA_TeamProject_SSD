#pragma once
#include "ICommand.h"
#include <string>
#include <vector>
using namespace std;

class IApplication;

class ReadCommand : public ICommand
{
public:
	ReadCommand(IApplication* app, const vector<string>& args);

	void execute();
	void check();

private:
	IApplication* _app;
	vector<string> _args;
};
