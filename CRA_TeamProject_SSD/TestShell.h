#pragma once

#include <vector>
#include <string>

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
	IApplication* _app;
	CommandFactory* _command_factory;
};
