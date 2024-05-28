#pragma once
#include <string>
#include "ShellCommand/CommandFactory.h"
#include <iostream>
#include <fstream>

using namespace std;

class IApplication
{
public:
	virtual ~IApplication() = default;
	virtual bool run() = 0;
	virtual void fullwrite(string data) = 0;
	virtual void fullread() = 0;

	CommandFactory* _command_factory;
};
