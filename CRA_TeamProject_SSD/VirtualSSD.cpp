#include "SSD.h"
#include <string>

class VirtualSSD : public SSD
{
public:
	void write(int lba, std::string data) override;
	std::string read(int lba) override;
};

void VirtualSSD::write(int lba, std::string data)
{

}

std::string VirtualSSD::read(int lba)
{
	return std::string("temp");
}