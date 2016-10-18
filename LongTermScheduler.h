#ifndef LONGTERMSCHEDULER_H
#define LONGTERMSCHEDULER_H
#include "Ram.h"
#include "PCB_list.h"

class LongTermScheduler
{
public:
	LongTermScheduler(Ram* setRam, PCB_list* setPCBlist, Disk* setdisk);
	~LongTermScheduler();
	void loadProcesses();
	void setPCB_list(PCB_list* setPCBlist) {	PCBlist = setPCBlist;}
	PCB** getReadyQueue() {return readyQueue;}
	void pop(PCB* process);
	void push();
	void sort(){PCBlist->sortPriority();}
	bool done(); 
	void setDisk(Disk* setdisk){ disk = setdisk;}
	
private:
	PCB_list *PCBlist;
	Disk *disk;
	Ram *ram;
	static const int queueCap = 1;
	PCB *readyQueue[queueCap];
	int queue;
	PCB *head;
};

#endif // LONGTERMSCHEDULER_H
