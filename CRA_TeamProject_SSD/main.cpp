#include "TestShell.h"
#include "VirtualSSD.h"
#include <string>
#include <sstream>
#include <csignal>

std::shared_ptr<TestShell> globalShell = nullptr;

void signalHandler(int signum) {
    globalShell.reset();
    exit(signum);
}

int main()
{
    auto shell = std::make_shared<TestShell>(new VirtualSSD());
    globalShell = shell;

    signal(SIGINT, signalHandler);

    std::string command;
    while (true) {
        std::cin.clear();
        std::cout << "$ ";
        std::getline(std::cin, command);
        try
        {
            shell->run(command);
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