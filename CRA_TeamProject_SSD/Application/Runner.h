#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include <map>

using namespace std;

class Runner : public IApplication
{
public:
	Runner(ISSD* ssd);

	bool run(const std::vector<std::string>& args) override;

private:
	map<string, IApplication*> _apps;
};
