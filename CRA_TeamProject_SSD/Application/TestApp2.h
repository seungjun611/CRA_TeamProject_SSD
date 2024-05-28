#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include <vector>

using namespace std;

class TestApp2 : public IApplication
{
public:
	TestApp2(ISSD* ssd);

	void setLbaRepeatly(const std::vector<int> lbas, const string value, const int repeat);

	bool readVerify(const int startLBA, const int endLBA, const std::string& writeData);

	bool run(const std::vector<std::string>& args) override;

private:
	ISSD* ssd;
	int MIN_LBA;
	int MAX_LBA;
};
