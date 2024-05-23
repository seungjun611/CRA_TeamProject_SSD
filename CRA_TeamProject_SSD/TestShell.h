#pragma once

#include "TestApplication.cpp"
#include <vector>
#include <string>

using namespace std;

class TestApplication;
class CommandFactory;

class TestShell
{
public:
	TestShell() = default;
	TestShell(ISSD* ssd);
	~TestShell() = default;

	void run(const string& command);
	vector<string> parse(const string& command);

private:
	TestApplication* _app;
	CommandFactory* _command_factory;
};
