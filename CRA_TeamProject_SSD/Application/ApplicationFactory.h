#pragma once

#include <string>
#include "../IApplication.h"
#include "../../SSD/ISSD.h"

class ApplicationFactory
{
public:
	IApplication* getApplication(const std::string& app_name, ISSD* ssd);
	static ApplicationFactory* getInstance();

private:
	static ApplicationFactory* _instance;
	ApplicationFactory() = default;
};