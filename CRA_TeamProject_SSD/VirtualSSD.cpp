#include "ISSD.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class VirtualSSD : public ISSD
{
public:
	void write(int lba, int data) override;
	std::string read(int lba) override;
	~VirtualSSD() {
		// cache ->nand.txt
	}

private:
	vector<map<int, int>> cache;
};

void VirtualSSD::write(int lba, int data)
{

}

std::string VirtualSSD::read(int lba)
{
	return std::string("temp");
}