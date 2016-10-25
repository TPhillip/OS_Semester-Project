#ifndef LONGTERMSCHEDULER_H
#define LONGTERMSCHEDULER_H
#include "Ram.h"
#include "PCB_list.h"

class LongTermScheduler
{
public:
	LongTermScheduler(Ram* setRam, PCB_list* setPCBlist, Disk* setdisk, PCB **setReadyQueue, int queueCap);
	~LongTermScheduler();
	void loadProcesses();
	void setPCB_list(PCB_list* setPCBlist) {	PCBlist = setPCBlist;}
	int getQueueLength() {return queue;}
	PCB* pop(PCB* process);
	void push();
	void sort(){PCBlist->sortPriority();}
	bool done(); 
	void setDisk(Disk* setdisk){ disk = setdisk;}
	
private:
	PCB_list *PCBlist;
	Disk *disk;
	Ram *ram;
	PCB **readyQueue;
	int queue, queueCap;
	PCB *head;
};

#endif // LONGTERMSCHEDULER_H
