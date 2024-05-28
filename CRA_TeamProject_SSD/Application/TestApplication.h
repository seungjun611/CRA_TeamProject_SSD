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

class TestApplication : public IApplication
{
public:
	TestApplication(ISSD* ssd) : ssd{ ssd } {
		MIN_LBA = ssd->getMinLBA();
		MAX_LBA = ssd->getMaxLBA();
		_command_factory = CommandFactory::getInstance(ssd);
	}

	bool run(const std::vector<std::string>& args) override
	{
		return true;
	}

	void fullwrite(string data) override {
		for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
			ssd->WRITE(lba, data);
		}
	}

	void fullread() override {
		for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
			ssd->READ(lba);
			cout << ssd->getReadData() << endl;
		}
	}

	void set_ssd(ISSD* ssd_) {
		ssd = ssd_;
	}

	ISSD* ssd;
	int MIN_LBA;
	int MAX_LBA;
};
