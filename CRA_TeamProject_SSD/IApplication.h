#pragma once
#include <string>
#include <vector>

using namespace std;

class IApplication
{
public:
	virtual ~IApplication() = default;
	virtual bool run(const std::vector<std::string>& args) = 0;
};
