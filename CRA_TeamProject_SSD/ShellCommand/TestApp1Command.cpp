#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "TestApp1Command.h"
#include "../Application/TestApplication.h"

using namespace std;

TestApp1Command::TestApp1Command(ISSD* ssd, const vector<string>& args) :
    _ssd{ ssd }, _args{ args }
{

}

void TestApp1Command::execute()
{
    this->check();
    //_app->runTestApp1();
}

void TestApp1Command::check()
{
    assertInvalidNumberOfArgument(_args, "testapp1", 1);
}
