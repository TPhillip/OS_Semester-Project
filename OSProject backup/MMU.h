#pragma once
#include "RAM.h"
#include "Disk.h"
#include <vector>
#include <string>
#include "PCB.h"
#include "Metrics.h"
#include <string>
#include <iostream>
class MMU {
private:
	struct Page {
		int address;
		bool valid = false;
	};
	struct Frame {
		int address;
		bool valid = false;
	};
	std::vector<Page> *pageTableVector;
	std::vector<Frame> *frameTableVector;
	int maxNumFrames;
	int maxNumPages;
	RAM *evga1024;
	Disk *seagate2048;
	bool busy = false;
	Metrics *stat;
	

public:
	//Determine if a given RAM slot is free
	bool ram_address_available(int addr, PCB *pcb);

	//Determine if a given DISK slot is free
	bool disk_address_available(int addr);
	//Returns starting address of first contiguious free RAM chunk (-1 if not available)
	int find_empty_frame();

	//Returns starting address of first contiguious free DISK chunk (-1 if not available)
	int find_empty_page();
	
	//creates new page to DISK and returns its number to the requesting proces
	void createPage(int instruction_number);
	void createFrame(int instruction_number);

	//Clear a page's ram addresses and clear the corresponding frames from ram
	void clearPage(int pageNum);
	void clearFrames(PCB *pcb);

	//write a word to RAM (Only works if page is in RAM)
	void write_to_disk(int pageNum, int offset, string toWrite);
	void write_to_ram(int frameNum, int offset, string entry, PCB *pcb);

	//read a word from RAM. If page is not in RAM, returns ermpty string
	string read_from_ram(int pageNum, int offset);
	string read_from_disk(int pageNum, int offset);

	//Determines whether a given page is in RAM or not
	bool is_page_in_ram(int pageNum);

	//service page fault (load to ram)
	void service_page_fault(PCB *pcb);

	bool is_busy()const{ return busy; }
	void set_busy(const bool value) { busy = value; }
	

	//constructor
	MMU(Disk *disk, RAM *ram, Metrics *_stat) {
		stat = _stat;
		evga1024 = ram;
		seagate2048 = disk;
		maxNumFrames = 1024 / 4;
		maxNumPages = 2048 / 4;
		pageTableVector = new vector<Page>;
		frameTableVector = new vector<Frame>;
		for (int i = 0; i < maxNumPages; ++i) {
			createPage(i);
		}
		for (int i = 0; i < maxNumFrames; ++i) {
			createFrame(i);
		}
	}
};