#ifndef DISPATCHER_H
#define DISPATCHER_H
#include "LongTermScheduler.h"
#include "cpu.h"
using namespace std;
class Dispatcher{
public:
	Dispatcher(CPU* setCPU, LongTermScheduler* setLTscheduler, PCB** setReadyQueue, Ram* setRam);
	~Dispatcher();
	void setCPU();
	
private:
	CPU* cpu;
	LongTermScheduler *LTscheduler;
	PCB** readyQueue;
	Ram *ram;
};

#endif //DISPATCHER_H