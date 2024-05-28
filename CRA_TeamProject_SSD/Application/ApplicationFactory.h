#pragma once

#include <string>
#include "../IApplication.h"
#include "../../SSD/ISSD.h"
#include "../ShellCommand/CommandFactory.h"

class ApplicationFactory
{
public:
	IApplication* getApplication(const std::string& app_name, ISSD* ssd);
	static ApplicationFactory* getInstance();
	CommandFactory* _command_factory;

private:
	static ApplicationFactory* _instance;
	ApplicationFactory() = default;
};