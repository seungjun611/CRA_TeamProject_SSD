#pragma once
#include "ICommand.h"
#include "TestApp2Command.h"
#include "../TestApplication.cpp"

using namespace std;

TestApp2Command::TestApp2Command(TestApplication* app, const vector<string>& args) :
    _app{ app }, _args{ args }
{

}

void TestApp2Command::execute()
{
    this->check();
    _app->runTestApp2();
}

void TestApp2Command::check()
{
    assertInvalidNumberOfArgument(_args, "testapp2", 1);
}
