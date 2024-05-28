#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include "../ShellCommand/ICommand.h"
#include "ApplicationFactory.h"
#include "Runner.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

Runner::Runner(ISSD* ssd)
{
	ApplicationFactory* app_factory = ApplicationFactory::getInstance();
	_apps.insert({ string("FullWriteReadCompare"), app_factory->getApplication(string("FullWriteReadCompare"), ssd) });
	_apps.insert({ string("FullRead10AndCompare"), app_factory->getApplication(string("FullRead10AndCompare"), ssd) });
	_apps.insert({ string("Write10AndCompare"), app_factory->getApplication(string("Write10AndCompare"), ssd) });
}

vector<string> Runner::_getScriptList(const vector<string>& args)
{
	ifstream script_file(args[1]);

	if (false == script_file.good())
	{
		throw std::runtime_error("파일이 존재하지 않습니다 : " + args[1]);
	}

	if (false == script_file.is_open())
	{
		throw std::runtime_error("파일이 열리지 않습니다 : " + args[1]);
	}

	std::string script;
	vector<string> script_list;
	while (std::getline(script_file, script))
	{
		script_list.push_back(script);
	}

	return script_list;
}

IApplication* Runner::_findApplication(const string& script)
{
	auto app = _apps.find(script);

	if (app == _apps.end())
	{
		throw std::runtime_error("등록된 스크립트를 찾을 수 없습니다 : " + script);
	}

	return app->second;
}

bool Runner::run(const vector<string>& args)
{
	try
	{
		vector<string> scripts = _getScriptList(args);
		for (auto script : scripts)
		{
			auto app = _findApplication(script);
			cout << script << " --- Run...";
			bool pass = app->run(args);
			if (pass == true)
			{
				cout << "Pass" << endl;
			}
			else
			{
				cout << "FAIL!" << endl;
			}
		}
		
	}
	catch (std::exception& e)
	{
		throw e;
	}

	return true;
}
