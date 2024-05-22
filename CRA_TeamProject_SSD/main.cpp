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
        try
        {
            shell.run(command);
        }
        catch(std::exception e)
        {
            if (std::string(e.what()) == "프로그램을 종료합니다") {
                return 0;
            }
            cout << e.what() << endl;
        }
    }
}