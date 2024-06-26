﻿#include "TestShell.h"
#include "../SSD/VirtualSSD.cpp"
#include "Application/TestApplication.h"
#include <string>
#include <sstream>
#include <csignal>

bool g_running = true;

void signalHandler(int signum) {
    g_running = false;
}

int main(int argc, char* argv[])
{
    VirtualSSD ssd;
    TestShell shell(&ssd);

    signal(SIGINT, signalHandler);

    if (argc == 2)
    {
        std::string filename = argv[1];
        std::string command = "runner " + filename;
        try
        {
            shell.run(command);
        }
        catch (std::exception& e)
        {
            std::cout << string(e.what()) << endl;
            return 1;
        }
        return 0;
    }

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
