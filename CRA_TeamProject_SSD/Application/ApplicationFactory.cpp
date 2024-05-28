#pragma once
#include "ApplicationFactory.h"
#include "TestApplication.h"
#include "TestApp1.h"
#include "TestApp2.h"
#include "FullWriteReadCompare.h"
#include "FullRead10AndCompare.h"
#include "Write10AndCompare.h"
#include "Loop_WriteAndReadCompare.h"
#include "AlwaysFail.h"
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
	else if (app_name == string("FullRead10AndCompare"))
	{
		return new FullRead10AndCompare(ssd);
	}
	else if (app_name == string("Write10AndCompare"))
	{
		return new Write10AndCompare(ssd);
	}
	else if (app_name == string("Loop_WriteAndReadCompare"))
	{
		return new Loop_WriteAndReadCompare(ssd);
	}
	else if (app_name == string("AlwaysFail"))
	{
		return new AlwaysFail(ssd);
	}
	else
	{
		return nullptr;
	}
}