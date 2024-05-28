#pragma once
#include <string>
#include "ShellCommand/CommandFactory.h"
#include <iostream>
#include <fstream>

using namespace std;

class IApplication
{
public:
	virtual ~IApplication() = default;
	virtual bool run() = 0;

	std::string read(int lba) {
		vector<string> args;
		args.push_back("read");
		args.push_back(std::to_string(lba));
		_command_factory->getCommand(args)->execute();

		string filename = "result.txt";
		std::ifstream file(filename);
		if (!file) {
			return "";
		}
		std::string line;
		while (std::getline(file, line)) {}
		file.close();
		return line;
	}

	void write(int lba, string data) {
		vector<string> args;
		args.push_back("write");
		args.push_back(std::to_string(lba));
		args.push_back(data);
		_command_factory->getCommand(args)->execute();
	}

	void fullread() {
		vector<string> args;
		args.push_back("fullread");
		_command_factory->getCommand(args)->execute();
	}

	void fullwrite(string data) {
		vector<string> args;
		args.push_back("fullwrite");
		args.push_back(data);
		_command_factory->getCommand(args)->execute();
	}

	void erase_size(int lba, int size) {
		vector<string> args;
		args.push_back("erase");
		args.push_back(std::to_string(lba));
		args.push_back(std::to_string(size));
		_command_factory->getCommand(args)->execute();
	}

	void erase_range(int start_lba, int end_lba) {
		vector<string> args;
		args.push_back("erase_range");
		args.push_back(std::to_string(start_lba));
		args.push_back(std::to_string(end_lba));
		_command_factory->getCommand(args)->execute();
	}

	CommandFactory* _command_factory;
};
