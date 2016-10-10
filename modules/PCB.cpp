#include "PCB.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
using namespace std;
PCB::PCB()
{
	jobInstructs = new int;
	*jobInstructs = 30;
	*jobInstructions = new int[*jobInstructs];
	diskData =  new int;
	*diskData = 44;
	*dataDisk = new int[*diskData];
	ramData =  new int;
	*ramData =25;
	*dataRam = new int[*ramData];
	outputSize =  new int;
	*outputSize =1;
	*output = new int[*outputSize];
	tempSize =  new int;
	*tempSize =1;
	*temp = new int[*tempSize];
	countJobs =   new int;
	*countJobs = 0;
	countDiskData=  new int;
	*countDiskData= 0;
	countRamData =   new int;
	*countRamData = 0;
	countOutput =   new int;
	*countOutput = 0;
	countTemp =   new int;
	*countTemp = 0;
	next = NULL;
	prev = NULL;
	ID = new string;
	*ID = "";
}

PCB::~PCB()
{
	
}
void PCB::setJobID(string *jobID){
	ID = jobID;
}
string* PCB::getJobID(){
	return ID;
}
PCB* PCB::getNext(){
	return next;
}
void PCB::setNext(PCB *nextPCB){
	next = nextPCB;
}
void PCB::addJobInstructions(int *location){
	//if(countJobs == jobInstructs){
		//increaseJobs();
	//}
	jobInstructions[*countJobs]=location;
	*countJobs+=1;
}
void PCB::addDataDisk(int *location){
	//if(countDiskData == diskData){
		//increaseDataDisk();
	//}
	dataDisk[*countDiskData]=location;
	*countDiskData+=1;
}
void PCB::addDataRam(int *location){
	//if(*countRamData == *ramData){
		//increaseDataRam();
	//}
	dataRam[*countRamData]=location;
	*countRamData+=1;
}
void PCB::addOutput(int *location){
	
}
void PCB::addTemp(int *location){
	
}
void PCB::increaseJobs(){
	
}
void PCB::increaseDataDisk(){
	
}
void PCB::increaseDataRam(){
	
}
void PCB::increaseOutput(){
	
}
void PCB::increaseTemp(){
	
}
void PCB::printPCB(){
	cout << "Job ID\t" << *ID << endl;
	cout << "Job Instructions\t" << *countJobs << endl;
	cout << "Disk Data info\t" << *countDiskData << endl;
}
