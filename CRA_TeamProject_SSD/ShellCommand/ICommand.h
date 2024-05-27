#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include "../../SSD/ISSD.h"

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
    static void assertInvalidLBA(string sLBA) {
        try {
            int lba = std::stoi(sLBA);
            if (lba < 0 || lba >= 100) {
                throw std::invalid_argument("lba 값은 0 이상 100 미만 정수이어야 한다");
            }
        }
        catch (std::exception& e) {
            throw e;
        }
    }
    static void assertInvalidDataType(string sData) {
        if (sData[0] != '0' || sData[1] != 'x') {
            throw std::invalid_argument("data type 은 hex 여야 한다");
        }
    }
    static void assertInvalidDataLength(string sData) {
        if (sData.size() != 10) {
            throw std::invalid_argument("data 의 자리수는 8이어야 한다");
        }
    }

    static void assertMaxSize(string sLBA) {
        try {
            int lba = std::stoi(sLBA);
            if (lba < 0 || lba > 10) {
                throw std::invalid_argument("size 값은 0 이상 10 이하");
            }
        }
        catch (std::exception& e) {
            throw e;
        }
    }
};
