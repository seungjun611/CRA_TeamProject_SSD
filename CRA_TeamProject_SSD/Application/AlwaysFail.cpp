#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include "../ShellCommand/ICommand.h"
#include "AlwaysFail.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>

using namespace std;

AlwaysFail::AlwaysFail(ISSD* ssd) : ssd{ ssd } {
	MIN_LBA = ssd->getMinLBA();
	MAX_LBA = ssd->getMaxLBA();
}

bool AlwaysFail::run(const std::vector<std::string>& args)
{
	return false;
}
