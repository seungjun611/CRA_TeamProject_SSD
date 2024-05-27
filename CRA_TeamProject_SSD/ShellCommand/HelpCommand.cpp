#pragma once
#include "ICommand.h"
#include "../IApplication.h"
#include "HelpCommand.h"
#include "../Application/TestApplication.h"

using namespace std;

HelpCommand::HelpCommand(ISSD* ssd, const vector<string>& args) :
    _ssd{ ssd }, _args{ args }
{

}

void HelpCommand::execute()
{
    this->check();
	std::cout << "************************************" << std::endl;
	std::cout << "************COMMAND HELP************" << std::endl;
	std::cout << "************************************" << std::endl;
	std::cout << "*** [ShellProgram commands help] ***" << std::endl;
	std::cout << "** write: write to SSD / usage: write <LBA> <VALUE>" << std::endl;
	std::cout << "** read: read from SSD / usage: read <LBA>" << std::endl;
	std::cout << "** exit: exit program / usage: exit" << std::endl;
	std::cout << "** help: help command" << std::endl;
	std::cout << "** fullwrite: write at all LBAs / usage: fullwrite <VALUE>" << std::endl;
	std::cout << "** fullread: read all LBAs / usage: fullread" << std::endl;
	std::cout << "** testapp1: After fullwrite, check if fullread value is corrrect according to the written value./ usage: testapp1" << std::endl;
	std::cout << "** testapp2: After overwrite, read the LBA value to make sure LBA value is correct according to overwriten value/ usage: testapp2" << std::endl;
	std::cout << "** LBA range: 0 ~ 99" << std::endl;
	std::cout << "** VALUE range: 0x00000000 ~ 0xFFFFFFFF" << std::endl;
	std::cout << "***********************************" << std::endl;
	std::cout << std::endl;
}

void HelpCommand::check()
{
    assertInvalidNumberOfArgument(_args, "help", 1);
}
