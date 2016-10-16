#ifndef LONGTERMSCHEDULER_H
#define LONGTERMSCHEDULER_H
#include "Ram.h"
#include "PCB_list.h"

class LongTermScheduler
{
public:
	LongTermScheduler();
	~LongTermScheduler();
	void loadProcesses(bool priority);
	void setPCB_list(PCB_list *setPCBlist) {	PCBlist = setPCBlist;}
	
private:
	PCB_list *PCBlist;
	Ram *ram;
	int queueCap;
	PCB **readyQueue;
	int queue;
};

#endif // LONGTERMSCHEDULER_H
