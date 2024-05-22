#pragma once

#include <vector>
#include <string>

using namespace std;

class TestShell
{
public:
	TestShell() = default;
	void run();
	vector<string> parse(const string& command);
	void execute(const vector<string>& args);
};