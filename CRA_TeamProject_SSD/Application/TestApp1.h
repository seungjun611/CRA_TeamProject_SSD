#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <random>

using namespace std;

class TestApp1 : public IApplication
{
public:
	TestApp1(ISSD* ssd);

	bool readVerify(const int startLBA, const int endLBA, const std::string& writeData);

	string makeRandomDataPattern();

	bool run() override;
	void fullwrite(string data) override;
	void fullread() override;

	ISSD* ssd;
	int MIN_LBA;
	int MAX_LBA;
};
