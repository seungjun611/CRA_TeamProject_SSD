#pragma once
#include "ICommand.h"
#include "TestApp1Command.h"
#include "../TestApplication.cpp"

using namespace std;

TestApp1Command::TestApp1Command(TestApplication* app, const vector<string>& args) :
    _app{ app }, _args{ args }
{

}

void TestApp1Command::execute()
{
    this->check();
    _app->runTestApp1();
}

void TestApp1Command::check()
{
    assertInvalidNumberOfArgument(_args, "testapp1", 1);
}
