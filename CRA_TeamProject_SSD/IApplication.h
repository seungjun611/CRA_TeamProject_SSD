#pragma once
#include <string>

using namespace std;

class IApplication
{
public:
	virtual ~IApplication() = default;
	virtual void write(int lba, string data) = 0;
	virtual void read(int lba) = 0;
	virtual void help() = 0;
	virtual void fullwrite(string data) = 0;
	virtual void fullread() = 0;
	virtual bool runTestApp1() = 0;
	virtual bool runTestApp2() = 0;
};
