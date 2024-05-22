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

bool TestShell::run(const string& command)
{
    std::vector<std::string> args = parse(command);
    return execute(args);
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

bool TestShell::validCheck(const vector<string>& args) {

    if(args[0] == "write") {
        if (args.size() < 3) {
            return false;
        }
        if (args[1].size() != 1 || !isdigit(args[1][0])) {
            return false;
        }
        const std::string& lastArg = args.back();
        if (lastArg.size() < 3 || lastArg[0] != '0' || lastArg[1] != 'x') {
            return false;
        }
        for (size_t i = 2; i < lastArg.size(); ++i) {
            if (!isxdigit(lastArg[i])) {
                return false;
            }
        }
    }
    else if (args[0] == "read")
    {
        cout << "READ" << endl;
    }
    else if (args[0] == "exit")
    {
        return false;
    }
    else if (args[0] == "help")
    {

    }
    else if (args[0] == "fullwrite")
    {

    }
    else if (args[0] == "fullread")
    {

    }

    return true;
}


bool TestShell::execute(const vector<string>& args)
{
    if (args.empty()) {
        return true;
    }
    
    if (validCheck(args)) return false;

    if (args[0] == "write") {
        _app->write(std::stoi(args[1]), args[2]);
    }
    else if (args[0] == "read")
    {
        cout << "READ" << endl;
    }
    else if (args[0] == "exit")
    {
        return false;
    }
    else if (args[0] == "help")
    {

    }
    else if (args[0] == "fullwrite")
    {

    }
    else if (args[0] == "fullread")
    {

    }

    return true;
}
