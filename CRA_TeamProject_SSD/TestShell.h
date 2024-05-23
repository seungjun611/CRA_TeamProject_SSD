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
	~TestShell();

	void run(const string& command);
	vector<string> parse(const string& command);
	void check(const vector<string>& args);
	void execute(const vector<string>& args);

private:
	TestApplication* _app;
};