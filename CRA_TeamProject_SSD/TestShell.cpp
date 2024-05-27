#include "../SSD/ISSD.h"
#include "IApplication.h"
#include "TestShell.h"
#include "ShellCommand/ICommand.h"
#include "ShellCommand/CommandFactory.h"
#include "Application/TestApplication.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <map>
#include "Application/ApplicationFactory.h"

using namespace std;

TestShell::TestShell(ISSD* ssd) :
    _apps{},
    _command_factory{new CommandFactory(ssd)}
{
    ApplicationFactory* app_factory = ApplicationFactory::getInstance();
    _apps.insert({ string("TestApplication"), app_factory->getApplication(string("TestApplication"), ssd) });
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
