#include "ISSD.h"
#include "TestShell.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

TestShell::TestShell(ISSD* ssd) :
    _app{new TestApplication()}
{
    _app->set_ssd(ssd);
}

void TestShell::run(const string& command)
{
    std::vector<std::string> args = parse(command);
    execute(args);
}

vector<string> TestShell::parse(const string& command) {
    std::vector<std::string> args;
    std::string arg;
    std::istringstream iss(command);
    while (iss >> arg) {
        args.push_back(arg);
    }
    return args;
}

void TestShell::execute(const vector<string>& args)
{
    if (args.empty()) {
        return;
    }

    if (args[0] == "write") {
        _app->write(std::stoi(args[1]), args[2]);
    }
    else if (args[0] == "read")
    {
        _app->read(std::stoi(args[1]));
    }
    else if (args[0] == "exit")
    {
    }
    else if (args[0] == "help")
    {
        _app->help();
    }
    else if (args[0] == "fullwrite")
    {
        _app->fullwrite(args[1]);
    }
    else if (args[0] == "fullread")
    {
        _app->fullread();
    }

    return;
}
