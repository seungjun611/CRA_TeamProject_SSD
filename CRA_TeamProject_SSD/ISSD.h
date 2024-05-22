#pragma once
#include <string>

class ISSD
{
public:
	virtual void write(int lba, int data) = 0;
	virtual std::string read(int lba) = 0;
};