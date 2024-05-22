#include "ISSD.h"
#include <iostream>

const int MIN_LBA = 0;
const int MAX_LBA = 99;

class TestApplication {
public:
	void write(int lba, int data) {
		ssd->write(lba, data);
	}

	void read(int lba) {
		ssd->read(lba);
	}

	void exit() {
		//TBD. cache 값 저장
	}

	void help() {
		std::cout << "************************************" << std::endl;
		std::cout << "******************HELP**************" << std::endl;
	}

	void fullwrite(int data) {
		for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
			ssd->write(lba, data);
		}		
	}

	void fullread() {
		for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
			ssd->read(lba);
		}
	}

	void set_ssd(ISSD* ssd_) {
		ssd = ssd_;
	}

	ISSD* ssd;
};