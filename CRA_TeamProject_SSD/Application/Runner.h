#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include <map>
#include <vector>
#include <fstream>

using namespace std;

class Runner : public IApplication
{
public:
	Runner(ISSD* ssd);

	bool run(const vector<string>& args) override;
	vector<string> _getScriptList(const vector<string>& args);
	IApplication* _findApplication(const string& script);

private:
	map<string, IApplication*> _apps;
};
