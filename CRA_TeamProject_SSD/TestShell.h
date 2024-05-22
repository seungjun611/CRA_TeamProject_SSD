#pragma once

#include "TestApplication.cpp"
#include <vector>
#include <string>

using namespace std;

class TestShell
{
public:
	TestShell() = default;
	void run();
	vector<string> parse(const string& command);
	bool execute(const vector<string>& args);

	TestApplication* app;
};