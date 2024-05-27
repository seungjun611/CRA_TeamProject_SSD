#pragma once
#include "ICommand.h"
#include <string>
#include <vector>
using namespace std;

//class IApplication;

class WriteCommand : public ICommand
{
public:
	WriteCommand(ISSD* ssd, const vector<string>& args);

	void execute();
	void check();
	void sendWriteSSDCmd(int lba, string data);

private:
	ISSD* _ssd;
	vector<string> _args;

};
