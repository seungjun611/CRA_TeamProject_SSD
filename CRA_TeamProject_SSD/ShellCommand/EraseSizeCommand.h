#pragma once
#include "ICommand.h"
#include <string>
#include <vector>
using namespace std;

class IApplication;

class EraseSizeCommand : public ICommand
{
public:
	EraseSizeCommand(ISSD* ssd, const vector<string>& args);

	void execute();
	void check();
	void sendEraseSizeSSDCmd(int lba, int size);

private:
	ISSD* _ssd;
	vector<string> _args;

};
