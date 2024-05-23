#pragma once
#include "ICommand.h"
#include <string>
#include <vector>

using namespace std;

class ExitCommand : public ICommand
{
public:
	ExitCommand(const vector<string>& args);

	void execute();
	void check();

private:
	vector<string> _args;
};

