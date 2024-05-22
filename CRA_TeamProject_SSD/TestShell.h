#pragma once

#include "TestApplication.cpp"
#include <vector>
#include <string>

using namespace std;

class TestShell
{
public:
	TestShell(ISSD* ssd);
	void run(const string& command);
	vector<string> parse(const string& command);
	void execute(const vector<string>& args);

	TestApplication* _app;
};