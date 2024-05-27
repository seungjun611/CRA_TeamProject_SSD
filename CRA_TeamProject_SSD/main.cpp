#include "TestShell.h"
#include "../SSD/VirtualSSD.cpp"
#include "TestApplication.cpp"
#include "Logger.cpp"
#include <string>
#include <sstream>
#include <csignal>

bool g_running = true;

void signalHandler(int signum) {
    g_running = false;
}

int main()
{
    VirtualSSD ssd;
    TestShell shell(&ssd);

    signal(SIGINT, signalHandler);

    //Logger& log = Logger::getInstance();
    //log.checkLogFile();

    std::string command;
    while (g_running) {
        std::cin.clear();
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

    return 0;
}