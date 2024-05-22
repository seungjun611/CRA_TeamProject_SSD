#include "SSD.h"
#include <iostream>

const int MIN_LBA = 0;
const int MAX_LBA = 99;

class TestApplication {
public:
	void write(int lba, std::string data) {
		ssd->write(lba, data);
	}

	void read(int lba) {
		ssd->read(lba);
	}

	void exit() {
		//TBD. cache °ª ÀúÀå
	}

	void help() {
		std::cout << "************************************" << std::endl;
		std::cout << "******************HELP**************" << std::endl;
	}

	void fullwrite(std::string data) {
		for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
			ssd->write(lba, data);
		}		
	}

	void fullread() {
		for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
			ssd->read(lba);
		}
	}

	void set_ssd(SSD* ssd_) {
		ssd = ssd_;
	}

	SSD* ssd;
};