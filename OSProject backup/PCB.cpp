#include "PCB.h"

/*PCB::PCB()
{
}

PCB::~PCB()
{
}*/
void PCB:: clear_cache_reg() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
				cache_copy[i][j] = "";
		}
	}
	for (int i = 0; i < 16; ++i) {
		reg_copy[i] = 0;
	}
	for (int i = 0; i < 4; ++i) {
		cache_page_copy[i] = -1;
	}
}

void PCB::set_reg_copy(int reg[16]) {
	for (int i = 0; i < 16; ++i) {
		reg_copy[i] = reg[i];
	}
}
void PCB::set_cache_copy(string cache[4][4]) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
				cache_copy[i][j] = cache[i][j];
		}
	}
}
void PCB::set_cache_page_copy(int cache_page[4]) {
	for (int i = 0; i < 4; ++i) {
		cache_page_copy[i] = cache_page[i];
	}
}
void PCB::set_new_frame(const int value, const int pageNum) {
	int i = 0;
	for (vector<Frame>::iterator it = page_table->begin(); it != page_table->end(); ++it) {
		if (i == pageNum) {
			it->frame = value;
			it->valid = true;
			break;
		}
		++i;
	}
}