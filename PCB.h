#ifndef PCB_H
#define PCB_H
#include <string>
#include <stddef.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "disk.h"
#include "Ram.h"
using namespace std;
class PCB
{
public:
	struct numGivenInfo{
		int input, output, temp, jobInstructs, numRamData, jobID;
		static const int numDiskData =44;
		~numGivenInfo(){};
	};
	struct counters{
		int countJobs, countDiskData, countRamData, countOutput, countTemp;
		
	};
	struct arrays{
		int *jobInstructions, *dataDisk, *dataRam, *inputBuffer, *outputBuffer, *tempBuffer;
		~arrays(){
			delete[] jobInstructions, delete[] dataDisk, delete[]  dataRam, delete[] inputBuffer,delete[] outputBuffer, delete[] tempBuffer;
			}
	};
	struct ramStruct{
		int programCounter, ramData, ramInputBuffer, ramOutputBuffer, ramTempBuffer;
	};
	PCB();
	PCB(int jobID, int numJobs, int priority);
	~PCB();
	void setID(int jobID, int numJobs, int priority);
	int getJobID() {	return ID;}
	PCB* getNext() {	return next;}
	PCB* getPrev() {	return prev;}
	void setNext(PCB *nextptr)	{next = nextptr;}
	void setPrev(PCB *prevptr)	{prev = prevptr;}
	struct numGivenInfo* getNumGivenInfo(){return &progInstructions;}
	struct counters* getCounters() { return &pcbCounters;}
	struct ramStruct* getRamUsage() { return &pcbRamStruct;}
	struct arrays* getDiskUsage() { return &pcbArrays;}
	int getPriority() {	return priority; }
	void addJobInstructions(int *location);
	void addDataDisk(int *location);
	void addDataRam(int *location);
	void setBuffer(int setInput, int setOutput, int setTemp);
	void addInput(int *input);
	void addOutput(int *location);
	void addTemp(int *location);
	void setProgramCounter(int ramLocation);
	void printPCB(Disk *disk);
private:
	int ID;
	PCB *next;
	PCB *prev;	
	int numRamData;
	int programCounter;
	int priority;
	numGivenInfo progInstructions;
	counters pcbCounters;
	arrays pcbArrays;
	ramStruct pcbRamStruct;
	//registers
	
	
	
};

#endif // PCB_H
