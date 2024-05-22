#include "ISSD.h"
#include "TestShell.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void TestShell::run()
{
    std::string command;

    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, command);

        std::vector<std::string> args = parse(command);
        execute(args);
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

void TestShell::execute(const vector<string>& args)
{
    if (args.empty()) {
        return;
    }

    if (args[0] == "write") {
        cout << "WRITE" << endl;
    }
    else if (args[0] == "read")
    {
        cout << "READ" << endl;
    }
    else if (args[0] == "exit")
    {

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

    return;
}
