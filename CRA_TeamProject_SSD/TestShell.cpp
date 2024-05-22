#include "ISSD.h"
#include "TestShell.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

TestShell::TestShell(ISSD* ssd) :
    _app{new TestApplication()}
{
    _app->set_ssd(ssd);
}

void TestShell::run(const string& command)
{
    std::vector<std::string> args = parse(command);

    try {
        check(args);
    }
    catch (std::invalid_argument e)
    {
        throw e;
    }

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

void TestShell::check(const vector<string>& args)
{
    if (args[0] == "write") {
        if (args.size() != 3) {
            throw std::invalid_argument("number or arguments are not 3");
        }

        int lba = std::stoi(args[1]);
        if (lba < 0 || lba > 100) {
            throw std::invalid_argument("lba 값은 0 이상 100 미만이어야 한다");
        }

        if (args[2][0] != '0' || args[2][1] != 'x') {
            throw std::invalid_argument("data type 은 hex 여야 한다");
        }

        if (args[2].size() != 10) {
            throw std::invalid_argument("data 의 자리수는 8이어야 한다");
        }
    }
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

    }
    else if (args[0] == "fullwrite")
    {

    }
    else if (args[0] == "fullread")
    {

    }

    return;
}
