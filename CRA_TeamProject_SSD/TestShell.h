#pragma once

#include <vector>
#include <string>
#include <map>

using namespace std;

class IApplication;
class ISSD;
class CommandFactory;

class TestShell
{
public:
	TestShell(ISSD* ssd);
	~TestShell() = default;

	void run(const string& command);
	vector<string> parse(const string& command);

private:
	map<string, IApplication*> _apps;
	CommandFactory* _command_factory;
};
