#ifndef CPU_H
#define CPU_H
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <math.h>
#include "Ram.h"
using namespace std;
class CPU{
public:
	CPU(Ram* setRam);
	~CPU();
	void set(int setJobID, int setOffset, int setInput, int setOutput, int setTemp, int setInputSize);
	void decode();
	string fetch(int index);
	int effectiveAddy(int address);
	void execute(int instructionType, string opcode, string regs[]);
	bool isDone(){ return done; }
	string hex2bin(string sHex);
	int hex2dec(string hex);
	int bin2dec(string bin);
	string dec2hex(int dec);
	
private:
	int pCount, jobID, offset, inputBuf, outputBuf, tempBuf, inputSize;
	bool done;
	string instruction;
	int cpuReg[16];
	Ram *ram;
};

#endif //CPU_H