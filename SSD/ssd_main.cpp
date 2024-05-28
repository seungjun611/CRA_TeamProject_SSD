#include "VirtualSSD.h"
#include <iostream>
#include <fstream>

using namespace std;

void readAndDisplay(VirtualSSD& ssd, int lba) {
	ssd.READ(lba);
	cout << "Result : " << ssd.getReadData() << endl;
}

int main() {
	VirtualSSD ssd;

	readAndDisplay(ssd, 0);
	readAndDisplay(ssd, 5);
	ssd.WRITE(0, "0x11111111");
	ssd.WRITE(5, "0x12345678");
	readAndDisplay(ssd, 0);
	readAndDisplay(ssd, 5);
	ssd.ERASE(0, 3);
	ssd.WRITE(1, "0xAAAAAAAA");
	ssd.FLUSH();

	for (int lba = 11; lba < 25; lba++) {
		ssd.WRITE(lba, "0xBBBBBBBB");
	}

	for (int lba = ssd.getMinLBA(); lba <= ssd.getMaxLBA(); lba++) {
		ssd.ERASE(lba, 1);
	}
	ssd.FLUSH();

	string dataPattern = "0xAAABBCCDD";
	for (int lba = ssd.getMinLBA(); lba <= ssd.getMaxLBA(); lba++) {
		ssd.WRITE(lba, dataPattern);
	}
	for (int lba = ssd.getMinLBA(); lba <= ssd.getMaxLBA(); lba += 10) {
		ssd.ERASE(lba, 5);
	}
	dataPattern = "0xFFFFFFF";
	for (int lba = ssd.getMinLBA(); lba <= ssd.getMaxLBA(); lba += 2) {
		ssd.WRITE(lba, dataPattern);
	}
}