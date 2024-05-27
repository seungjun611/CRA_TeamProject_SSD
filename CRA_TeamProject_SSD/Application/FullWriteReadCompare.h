﻿#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include <vector>

using namespace std;

class FullWriteReadCompare : public IApplication
{
public:
	FullWriteReadCompare(ISSD* ssd);

	void fullwrite(string data);

	bool readVerify(const int startLBA, const int endLBA, const std::string& writeData);

	string makeRandomDataPattern();

	bool run(const std::vector<std::string>& args) override;

private:
	ISSD* ssd;
	int MIN_LBA;
	int MAX_LBA;
};
