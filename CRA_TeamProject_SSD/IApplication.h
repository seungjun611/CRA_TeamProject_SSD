#pragma once
#include <string>
#include <vector>
#include "ShellCommand/CommandFactory.h"
#include <iostream>
#include <fstream>

using namespace std;

class IApplication
{
public:
	virtual ~IApplication() = default;
	virtual bool run(const std::vector<std::string>& args) = 0;
	virtual void fullwrite(string data) = 0;
	virtual void fullread() = 0;

	CommandFactory* _command_factory;
};
