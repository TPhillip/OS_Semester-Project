#include "LongTermScheduler.h"

LongTermScheduler::LongTermScheduler()
{
	ram = new Ram();
	queue =0;
	queueCap = 1;
	PCB *temp;
	temp = new PCB[queueCap];
	*readyQueue = temp;
}

LongTermScheduler::~LongTermScheduler()
{
	delete [] ram;
}

void LongTermScheduler::loadProcesses(bool priority){
	if(priority){
		PCBlist->sortPriority();
	}
	PCB *head;
	head = PCBlist->getCurrent();
	int processRamSize, ramAvailable, ramLocation;
	PCB::numGivenInfo progInstructions = head->getNumGivenInfo();
	processRamSize = progInstructions.numRamData;
	ramAvailable = ram->getAvailable();
	if(ramAvailable > processRamSize && head != NULL){
		if(queue < queueCap){ 
			ramLocation = ram->getSize();
			head->setProgramCounter(ramLocation);
			readyQueue[queue]=head;
			queue+=1;
			head= head->getNext();
			cout << "Job\t" << progInstructions.jobID << endl;
		}
	}
	queue-=1;
}


