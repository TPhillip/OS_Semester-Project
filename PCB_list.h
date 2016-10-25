#ifndef PCB_LIST_H
#define PCB_LIST_H
#include "PCB.h"
//#include "disk.h"
#include <stddef.h>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
using namespace std;
class PCB_list
{
public:
	PCB_list();
	~PCB_list();
	void addPCB(int jobID, int numJobs, int priority);
	PCB* getHeadPtr() { return head;}
	PCB* getCurrent() { return current;}
	void setCurrent() {current = current->getNext();}
	int countPCB() {return count;}
	void addJobInstruction(int jobID, int *jobInstructLocation);
	void addData(int jobID, int *data);
	void addBuffer(int input, int output, int temp);
	void sortPriority();
	void placePrev(PCB *first, PCB *second);
	void placeNext(PCB *first, PCB *second);
	void printPCBInfo(Disk *disk);
	
private:
	PCB *head, *tail, *current;
	int count;
};

#endif // PCB_LIST_H
