#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "PCB.h"
#include "Disk.h"
#include "RAM.h"
#include "math.h"
#include "Metrics.h"
#include "MMU.h"

using namespace std;

class Scheduler
{
public:
	Scheduler(Disk *drive, PCB *PCB1, RAM *DDR3, Metrics *_stat, MMU *set_mmu, string coreDumpOutputFileName)
	{
		stat = _stat;
		to_read_from = drive;
		PCB2 = PCB1;
		to_write_to = DDR3;
		mmu = set_mmu;
		if (std::ofstream(coreDumpOutputFileName)) {
			remove(coreDumpOutputFileName.c_str());
		}
		
		outfile.open(coreDumpOutputFileName, std::ios_base::out);
		
	}	
	~Scheduler() {
		outfile.close();
	}

	//methods
	void run_scheduler();
	void check_for_completion();
	void load_processes();
	int hex_to_base10(string hex);
	

private: 
	Disk *to_read_from;
	PCB *PCB2;
	RAM *to_write_to;
	Metrics *stat;
	MMU *mmu;
	std::ofstream outfile;
};
#endif // SCHEDULER_H
