#pragma once
#include "ICommand.h"
#include <string>
#include <vector>
using namespace std;

//class IApplication;

class FlushCommand : public ICommand
{
public:
	FlushCommand(ISSD* ssd, const vector<string>& args);

	void execute();
	void check();
	void sendFlushSSDCmd();

private:
	ISSD* _ssd;
	vector<string> _args;

};
