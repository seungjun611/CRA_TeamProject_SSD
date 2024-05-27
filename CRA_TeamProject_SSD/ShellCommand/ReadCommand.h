#pragma once
#include "ICommand.h"
#include <string>
#include <vector>
using namespace std;

class IApplication;

class ReadCommand : public ICommand
{
public:
	ReadCommand(ISSD* ssd, const vector<string>& args);

	void execute();
	void check();
	void sendReadSSDCmd(int lba);

private:
	ISSD* _ssd;
	vector<string> _args;
};
