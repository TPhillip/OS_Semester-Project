#ifndef DISPATCHER_H
#define DISPATCHER_H
#include "PCB.h"
#include "CPU.h"
#include "MMU.h"

using namespace std;

class Dispatcher
{
public:
	Dispatcher(PCB *PCB1, MMU *set_mmu)
	{
		PCB2 = PCB1;
		mmu = set_mmu;
	}

//methods
void dispatch(CPU *Intel);
void service_faults();
	
private:	
	PCB *PCB2;
	MMU *mmu;
};

#endif // DISPATCHER_H
