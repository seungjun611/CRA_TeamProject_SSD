﻿#pragma once
#include "ICommand.h"
#include "FullReadCommand.h"
#include "../TestApplication.cpp"

using namespace std;

FullReadCommand::FullReadCommand(TestApplication* app, const vector<string>& args) :
    _app{ app }, _args{ args }
{

}

void FullReadCommand::execute()
{
    this->check();
    _app->fullread();
}

void FullReadCommand::check()
{
    assertInvalidNumberOfArgument(_args, "fullread", 1);
}