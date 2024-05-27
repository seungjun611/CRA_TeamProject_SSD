#include "VirtualSSD.h"
#include <iostream>
#include <fstream>

using namespace std;

void readTest(VirtualSSD& ssd, int lba) {
	SSDCommand cmd;

	cmd.opcode = OPCODE::R;
	cmd.param1 = lba;
	ssd.execute(cmd);

	ifstream file(ssd.RESULT_FILE_NAME);
	string ret;
	file >> ret;
	cout << "Result : " << ret << endl;
}

void writeTest(VirtualSSD& ssd, int lba, string data) {
	SSDCommand cmd;

	cmd.opcode = OPCODE::W;
	cmd.param1 = lba;
	cmd.param2 = data;
	ssd.execute(cmd);
}

int main() {
	VirtualSSD ssd;

	readTest(ssd, 0);
	readTest(ssd, 5);
	writeTest(ssd, 0, "0x11111111");
	writeTest(ssd, 5, "0x12345678");
	readTest(ssd, 0);
	readTest(ssd, 5);
	ssd.execute(SSDCommand{ OPCODE::E, 0, "", 3 });
	writeTest(ssd, 1, "0xAAAAAAAA");
	ssd.execute(SSDCommand{OPCODE::F, 0, "", 0});

	for (int lba = 11; lba < 25; lba++) {
		writeTest(ssd, lba, "0xBBBBBBBB");
	}
}