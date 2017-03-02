// Zane W. Gabriel K. Alex C. Tevin P. 

#ifndef CPU_H
#define CPU_H
#include "PCB.h"
#include "RAM.h"
#include <string>
#include <math.h>
#include <sstream>
#include <iostream>
#include "Metrics.h"
#include "MMU.h"

using namespace std;

class CPU
{
public:
	CPU(RAM *corsair, PCB *ProgList, Metrics *_stat, MMU *set_mmu)
	{
		stat = _stat;
		PCB2 = ProgList;
		ram = corsair;
		mmu = set_mmu;
		//Gigabyte = corsair;
		cpuReg[0] = 0; //this is the accumulator
		cpuReg[1] = 0; //this is the 0 regester
		opcode = "";
		clear_cache();
		for (int i = 0; i < 4; ++i) {
			cache_page[i] = -1;
		}
		
	}
	~CPU();


	//methods
	
	//this method takes in the initial Ram index, and sets it to starting_RAM_Location.
	void set_to_run(int start_index, PCB *PCBlist);
	
	//this gets the instructions from ram and decodes and writes to registers
	void decode_and_execute();

	void clear_cache();
	bool check_cache(int page);
	void load_cache(int page);
	string fetch(int ram_location);
	void set_cache(int ram_location, string entry);
	void set_cache_page_copy();
	int cache_address(int ram_location);
	int get_page(int program_index);
	bool get_page_fault() { return page_fault; }
	void printReg();
	
	//this gets the item from RAM
	//string fetch(int index);
	
	//this does some stuff tbd!!!!!!!!!!
	void execute();
	//void execute();
	
	//this method is getting the correct address in ram for the given logical address
	int effective_addy(int address);
	
	// converts hexadecimal to binary
	string hex_to_bin(string sHex);
	
	// converts hexadecimal to binary
	string bin_to_hex(string sBin);
	
	//converts hexadecimal to base 10
	int hex_to_base10(string hex);
	
	//converts binary to base 10
	int bin_to_base10(string bin);
	
	//this converts base 10 to Hexadecimal but it actually doesnt because we didnt write anything in the function body. !!!!!!!!!!!!!!!
	string base10_to_hex(int dec);
	
	string Base10_to_bin(int x);
	
	//getter methods
	bool isDone(){ return done; };


	void set_reg_copy();
	void set_cache_copy();
	
private:
		int starting_RAM_Location = 0;
		bool given_start = false;
		PCB *PCB2;
		//RAM *Gigabyte;
		RAM *ram;
		MMU *mmu;
		bool done = false;
		bool loadCache = false;
		//max index for each
		int max_instructs = 0;
		int max_input = 0;
		int max_output = 0;
		int max_temp = 0;
		int input_buffer = 0;
		int output_buffer = 0;
		int temp_buffer = 0;
		//PCB *current_PCB;
		string bin_instructions[6];
		int cpuReg[16];
		int instruction_type;
		string opcode;
		Metrics *stat;
		clock_t temp_stat;
		int cache_page[4];
		string cache[4][4];
		bool page_fault = false;
		//string instructions[4][2] = { 0 };
		//string input[4][2] = { 0 };
		//string output[4][2] = { 0 };
		//string temp[4][2] = { 0 };
		
};

#endif // CPU_H
