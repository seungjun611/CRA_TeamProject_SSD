#pragma once
#include "ApplicationFactory.h"
#include "TestApplication.h"
#include "TestApp1.h"
#include "TestApp2.h"
#include "FullWriteReadCompare.h"
#include "Runner.h"

using namespace std;

ApplicationFactory* ApplicationFactory::_instance = nullptr;

ApplicationFactory* ApplicationFactory::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ApplicationFactory();
	}
	return _instance;
}

IApplication* ApplicationFactory::getApplication(const string& app_name, ISSD* ssd)
{
	if (app_name == string("TestApplication"))
	{
		return new TestApplication(ssd);
	}
	else if (app_name == string("testapp1"))
	{
		return new TestApp1(ssd);
	}
	else if (app_name == string("testapp2"))
	{
		return new TestApp2(ssd);
	}
	else if (app_name == string("runner"))
	{
		return new Runner(ssd);
	}
	else if (app_name == string("FullWriteReadCompare"))
	{
		return new FullWriteReadCompare(ssd);
	}
	else
	{
		return nullptr;
	}
}