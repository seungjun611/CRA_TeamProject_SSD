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

void assertInvalidNumberOfArgument(const vector<string>& args, string command, int numArgument) {
    if (args.size() != numArgument) {
        string message = command.append(" command는 ").append(to_string(numArgument)).append("개의 argument 가 주어져야 한다");
        throw std::invalid_argument(message);
    }
}

void TestShell::check(const vector<string>& args)
{
    if (args[0] == "write") {
        assertInvalidNumberOfArgument(args, "write", 3);

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
    else if (args[0] == "read") {
        assertInvalidNumberOfArgument(args, "read", 2);

        int lba = std::stoi(args[1]);
        if (lba < 0 || lba > 100) {
            throw std::invalid_argument("lba 값은 0 이상 100 미만이어야 한다");
        }
    }
    else if (args[0] == "help") {
        assertInvalidNumberOfArgument(args, "help", 1);
    }
    else if (args[0] == "fullwrite") {
        assertInvalidNumberOfArgument(args, "fullwrite", 2);
        if (args[1][0] != '0' || args[1][1] != 'x') {
            throw std::invalid_argument("data type 은 hex 여야 한다");
        }

        if (args[1].size() != 10) {
            throw std::invalid_argument("data 의 자리수는 8이어야 한다");
        }
    }
    else if (args[0] == "fullread") {
        assertInvalidNumberOfArgument(args, "fullread", 1);
    }
    else if (args[0] == "testapp1") {
        assertInvalidNumberOfArgument(args, "testapp1", 1);
    }
    else if (args[0] == "testapp2") {
        assertInvalidNumberOfArgument(args, "testapp2", 1);
    }
    else if (args[0] == "exit") {
        assertInvalidNumberOfArgument(args, "exit", 1);
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

    if (args[0] == "write") {
        _app->write(std::stoi(args[1]), args[2]);
    }
    else if (args[0] == "read")
    {
        _app->read(std::stoi(args[1]));
    }
    else if (args[0] == "exit")
    {
        throw std::runtime_error("프로그램을 종료합니다");
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
    else if (args[0] == "testapp1")
    {
        _app->runTestApp1();
    }
    else if (args[0] == "testapp2")
    {
    }

    return;
}
