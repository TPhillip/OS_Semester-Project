#ifndef LOADER_H
#define LOADER_H
#include <string>
#include "PCB.h"
#include "Disk.h"
#include <Fstream>
#include <iostream>
#include <sstream>
#include "MMU.h"

using namespace std; 
 
//this class maintains the loader, which will take data from the provided .txt file, and loads its contents into Disk, while maintaing the PCB
class Loader
{
public:
	Loader(Disk *drive, PCB *PCB1, string file, int set_priority, MMU *set_mmu, string scheduleOutputFileName)
	{
		to_write_to = drive;
		to_edit = PCB1;
		head = PCB1;
		file_path = file;
		sortingAlgo = set_priority;
		mmu = set_mmu;
		num_instructions = 0;
		outfile.open(scheduleOutputFileName, std::ios_base::app);
	}
	~Loader();

	//methods
	void read_File();
	int hex_to_base10(string hex);
	PCB* get_headPtr() { return head; }
	
	private:
		Disk *to_write_to;
		PCB *to_edit, *head;
		MMU *mmu;
		string file_path;
		int num_instructions = 0;
		
		//set 0 for false or 1 for true
		int sortingAlgo;
		std::ofstream outfile;
};
#endif // LOADER_H
