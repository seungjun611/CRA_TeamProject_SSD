#pragma once
#include "ICommand.h"
#include <string>
#include <vector>
using namespace std;

class IApplication;

class EraseRangeCommand : public ICommand
{
public:
	EraseRangeCommand(ISSD* ssd, const vector<string>& args);

	void execute();
	void check();
	void sendEraseRangeSSDCmd(int start_lba, int end_lba);

private:
	ISSD* _ssd;
	vector<string> _args;

};
