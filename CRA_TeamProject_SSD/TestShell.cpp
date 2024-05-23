#include "ISSD.h"
#include "TestShell.h"
#include "ShellCommand/ICommand.h"
#include "ShellCommand/CommandFactory.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

TestShell::TestShell(ISSD* ssd) :
    _app{new TestApplication()},
    _command_factory{new CommandFactory(_app)}
{
    _app->set_ssd(ssd);
}

TestShell::~TestShell()
{
    delete _app;
}

void TestShell::run(const string& command)
{
    std::vector<std::string> args = parse(command);

    try {
        ICommand* new_command = _command_factory->getCommand(args);

        if (new_command != nullptr)
        {
            new_command->execute();
        }
    }
    catch (std::exception e)
    {
        throw e;
    }
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
