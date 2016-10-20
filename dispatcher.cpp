#include "dispatcher.h"


Dispatcher::Dispatcher(CPU *setCPU, LongTermScheduler *setLTscheduler, PCB** setReadyQueue, Ram* setRam){
	cpu = setCPU;
	LTscheduler = setLTscheduler;
	readyQueue = setReadyQueue;
	ram = setRam;
}

Dispatcher::~Dispatcher(){
	
}

void Dispatcher::setCPU(){
	PCB* pcb = readyQueue[0];
	LTscheduler->pop(pcb);
	PCB::numGivenInfo info = pcb->getNumGivenInfo();
	PCB::arrays pcbArrays = pcb->getDiskUsage();
	PCB::ramStruct pcbRamInfo = pcb->getRamUsage();
	//void set(int setJobID, int setOffset, int setInput, int setOutput, int setTemp, int setPC);
	int offset = pcbRamInfo.programCounter;
	int inputBuffer = pcbRamInfo.ramInputBuffer;
	int outputBuffer = pcbRamInfo.ramOutputBuffer;
	int tempBuffer = pcbRamInfo.ramTempBuffer;
	int jobID = pcb->getJobID();
	int inputBufferSize = info.input;
	cpu->set(jobID, offset, inputBuffer, outputBuffer, tempBuffer, inputBufferSize);
	
}