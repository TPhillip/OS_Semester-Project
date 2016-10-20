#include "LongTermScheduler.h"

LongTermScheduler::LongTermScheduler(Ram* setRam, PCB_list* setPCBlist, Disk* setdisk, PCB **setReadyQueue, int queueCap)
{
	ram = setRam;
	queue =0;
	PCBlist = setPCBlist;
	disk = setdisk;
	head = PCBlist->getHeadPtr();
	readyQueue = setReadyQueue;
}

LongTermScheduler::~LongTermScheduler()
{
	
}

void LongTermScheduler::loadProcesses(){
	if(queue < queueCap){
		int processRamSize, ramAvailable, ramLocation;
		PCB::numGivenInfo progInstructions = head->getNumGivenInfo();
		processRamSize = progInstructions.numRamData;
		ramAvailable = ram->getAvailable();
		if(ramAvailable > processRamSize){
				ramLocation = ram->getSize();
				head->setProgramCounter(ramLocation);
				push();
				queue+=1;
				head= head->getNext();
				PCBlist->setCurrent();
		}
	}
}
PCB* LongTermScheduler::pop(PCB* process){
	PCB* first = readyQueue[0];
	int index;
	if(queue>0){
		for(index = 0; index < queue; index++){
			if(process->getJobID() == readyQueue[index]->getJobID()){
				if(index+1 < queue){
					for(int i = index+1; i < queue; i++){
						readyQueue[i-1] = readyQueue[i];
					}
					queue--;
					readyQueue[queue] = NULL;
				}else{
				queue--;
				readyQueue[queue] = NULL;
				}
			}
		}
	}
	return first;
}

void LongTermScheduler::push(){
	readyQueue[queue]=head;
	PCB::arrays pcbArrays = head->getDiskUsage();
	PCB::numGivenInfo progInstructs = head->getNumGivenInfo();
	for(int i = 0; i < progInstructs.jobInstructs; i++){
		int index = pcbArrays.jobInstructions[i];
		ram->add(disk->get(index));
	}
}
bool LongTermScheduler::done(){
	if(head == NULL){
		cout << "No More processes available for ReadyQueue" << endl;
		return true;
	}else{
		return false;
	}
}


