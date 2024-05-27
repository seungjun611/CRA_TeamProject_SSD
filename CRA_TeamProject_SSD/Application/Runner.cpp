#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include "../ShellCommand/ICommand.h"
#include "ApplicationFactory.h"
#include "Runner.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>

using namespace std;

Runner::Runner(ISSD* ssd)
{
	ApplicationFactory* app_factory = ApplicationFactory::getInstance();
	_apps.insert({ string("FullWriteReadCompare"), app_factory->getApplication(string("FullWriteReadCompare"), ssd) });
}

bool Runner::run(const std::vector<std::string>& args)
{
	return true;
}
