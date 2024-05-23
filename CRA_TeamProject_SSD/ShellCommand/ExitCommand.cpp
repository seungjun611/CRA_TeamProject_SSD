#pragma once
#include "ICommand.h"
#include "ExitCommand.h"
#include <stdexcept>

using namespace std;

ExitCommand::ExitCommand(const vector<string>& args) : _args{ args }
{

}

void ExitCommand::execute()
{
    this->check();
    throw std::runtime_error("프로그램을 종료합니다");
}

void ExitCommand::check()
{
    assertInvalidNumberOfArgument(_args, "exit", 1);
}