#ifndef PCB_H
#define PCB_H
#include <string>
#include <stddef.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
using namespace std;
class PCB
{
public:
	PCB();
	~PCB();
	void setJobID(string *jobID);
	string* getJobID();
	PCB* getNext();
	void setNext(PCB *nextptr);
	void addJobInstructions(int *location);
	void addDataDisk(int *location);
	void addDataRam(int *location);
	void addOutput(int *location);
	void addTemp(int *location);
	void increaseJobs();
	void increaseDataDisk();
	void increaseDataRam();
	void increaseOutput();
	void increaseTemp();
	void printPCB();
private:
	string *ID;
	PCB *next;
	PCB *prev;
	int *jobInstructs;
	int *diskData;
	int *ramData;
	int *outputSize;
	int *tempSize;
	int *countJobs;
	int *countDiskData;
	int *countRamData;
	int *countOutput;
	int *countTemp;
	int *jobInstructions[];
	int *dataDisk[];
	int *dataRam[];
	int *output[];
	int *temp[];
};

#endif // PCB_H
