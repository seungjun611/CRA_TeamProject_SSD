#pragma once

#include "TestApplication.cpp"
#include <vector>
#include <string>

using namespace std;

class TestShell
{
public:
	TestShell() = default;
	TestShell(ISSD* ssd);

	bool run(const string& command);
	vector<string> parse(const string& command);
	bool execute(const vector<string>& args);
	bool validCheck(const vector<string>& args);

private:
	TestApplication* _app;
};