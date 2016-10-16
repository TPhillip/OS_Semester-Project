#include "PCB.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
using namespace std;
PCB::PCB(){
	
}
PCB::PCB(int jobID, int numJobs, int setpriority)
{
	next = NULL;
	prev = NULL;
	ID = jobID;
	progInstructions.jobID = ID;
	progInstructions.jobInstructs = numJobs;
	priority = setpriority;
	int *tempJobs, *tempData;	
	tempJobs = new int[progInstructions.jobInstructs];
	pcbArrays.jobInstructions = tempJobs;
	tempData = new int[progInstructions.numDiskData];
	pcbArrays.dataDisk = tempData;
}

PCB::~PCB()
{
	
}
void PCB::setID(int jobID, int numJobs, int setpriority){
	ID = jobID;
	progInstructions.jobID = ID;
	progInstructions.jobInstructs = numJobs;
	priority = setpriority;
	int *tempJobs, *tempData;	
	tempJobs = new int[progInstructions.jobInstructs];
	pcbArrays.jobInstructions = tempJobs;
	tempData = new int[progInstructions.numDiskData];
	pcbArrays.dataDisk = tempData;
}
void PCB::addJobInstructions(int *location){
	pcbArrays.jobInstructions[pcbCounters.countJobs]=*location;
	pcbCounters.countJobs+=1;
}
void PCB::addDataDisk(int *location){
	pcbArrays.dataDisk[pcbCounters.countDiskData]=*location;
	pcbCounters.countDiskData+=1;
}
void PCB::addDataRam(int *location){
	pcbArrays.dataRam[pcbCounters.countRamData]=*location;
	pcbCounters.countRamData+=1;
}
void PCB::setBuffer(int setInput, int setOutput, int setTemp){
	progInstructions.input = setInput;
	progInstructions.output = setOutput;
	progInstructions.temp = setTemp;
	int *tempInput, *tempOutput, *tempTemp;
	tempInput = new int[progInstructions.input];
	pcbArrays.inputBuffer = tempInput;
	tempOutput = new int[progInstructions.output];
	pcbArrays.outputBuffer = tempOutput;
	tempTemp = new int[progInstructions.temp];
	pcbArrays.tempBuffer = tempTemp;
	numRamData = progInstructions.jobInstructs + progInstructions.numDiskData + progInstructions.input + progInstructions.output + progInstructions.temp;
	//tempRam = new int[numRamData];
	progInstructions.numRamData = numRamData;
}
void PCB::addInput(int *location){
	
}
void PCB::addOutput(int *location){
	
}
void PCB::addTemp(int *location){
	
}
void PCB::setProgramCounter(int ramLocation) {
	pcbRamStruct.programCounter = ramLocation;
	pcbRamStruct.ramData = ramLocation + progInstructions.numDiskData;
	pcbRamStruct.ramInputBuffer = pcbRamStruct.ramData+ progInstructions.input;
	pcbRamStruct.ramOutputBuffer = pcbRamStruct.ramInputBuffer+ progInstructions.output;
	pcbRamStruct.ramTempBuffer = pcbRamStruct.ramOutputBuffer+ progInstructions.temp;
	
	}
void PCB::printPCB(Disk *disk){
	cout << "Job ID\t" << ID << endl;
	cout << "Priority\t" << priority << endl;
	cout << "jobInstructions Size\t" << progInstructions.jobInstructs << endl;
	cout << "Job Instructions\t" << pcbCounters.countJobs << endl;
	cout << "Disk Data info\t" << pcbCounters.countDiskData << endl;
	cout << "Input Buffer\t" << progInstructions.input << endl;
	cout << "Output Buffer\t" << progInstructions.output << endl;
	cout << "Temp Buffer\t" << progInstructions.temp << endl;
	cout << "Ram usage\t" << progInstructions.numRamData << endl;
	

}
