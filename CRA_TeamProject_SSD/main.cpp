#include "TestShell.h"
#include "VirtualSSD.h"
#include <string>
#include <sstream>

int main()
{
    VirtualSSD ssd;
    TestShell shell(&ssd);

    std::string command;
    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, command);
        if (shell.run(command) == false) break;
    }
}