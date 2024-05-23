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

void TestShell::run(const string& command)
{
    std::vector<std::string> args = parse(command);

    try {
        ICommand* new_command = _command_factory->getCommand(args);

        if (new_command != nullptr)
        {
            new_command->execute();
        }
        else
        {
            check(args);
            execute(args);
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

void assertInvalidNumberOfArgument(const vector<string>& args, string command, int numArgument) {
    if (args.size() != numArgument) {
        string message = command.append(" command는 ").append(to_string(numArgument)).append("개의 argument 가 주어져야 한다");
        throw std::invalid_argument(message);
    }
}

void TestShell::check(const vector<string>& args)
{
    if (args.size() == 0) {
        return;
    }
    else if (args[0] == "testapp1") {
        assertInvalidNumberOfArgument(args, "testapp1", 1);
    }
    else if (args[0] == "testapp2") {
        assertInvalidNumberOfArgument(args, "testapp2", 1);
    }
    else
    {
        throw std::invalid_argument("지원하지 않는 command 이다");
    }
}

void TestShell::execute(const vector<string>& args)
{
    if (args.empty()) {
        return;
    }
    else if (args[0] == "testapp1")
    {
        _app->runTestApp1();
    }
    else if (args[0] == "testapp2")
    {
        _app->runTestApp2();      
    }

    return;
}
