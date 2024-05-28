#pragma once

#include "../../SSD/ISSD.h"
#include "../IApplication.h"
#include <vector>

using namespace std;

class AlwaysFail : public IApplication
{
public:
	AlwaysFail(ISSD* ssd);

	bool run(const std::vector<std::string>& args) override;

private:
	ISSD* ssd;
	int MIN_LBA;
	int MAX_LBA;
};
