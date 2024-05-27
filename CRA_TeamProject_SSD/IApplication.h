#pragma once
#include <string>

using namespace std;

class IApplication
{
public:
	virtual ~IApplication() = default;
	virtual bool runTestApp1() = 0;
	virtual bool runTestApp2() = 0;
};
