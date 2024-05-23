#pragma once
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class ICommand
{
public:
	virtual void execute() = 0;
	virtual void check() = 0;

    static void assertInvalidNumberOfArgument(const vector<string>& args, string command, int numArgument) {
        if (args.size() != numArgument) {
            string message = command.append(" command는 ").append(to_string(numArgument)).append("개의 argument 가 주어져야 한다");
            throw std::invalid_argument(message);
        }
    }
};
