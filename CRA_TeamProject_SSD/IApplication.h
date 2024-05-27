#pragma once
#include <string>

using namespace std;

class IApplication
{
public:
	virtual ~IApplication() = default;
	virtual bool run() = 0;
};
