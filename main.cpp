#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "modules\loader.h"
#include "modules\LongTermScheduler.h"
#include "modules/cpu.h"
#include "modules/dispatcher.h"
								
int main(int argc, char **argv)
{

	Disk* disk = new Disk();
	PCB_list* PCBlist =  new PCB_list();
	Loader loader(PCBlist, disk);
	loader.readFile("C:\\Users\\gkigu\\OneDrive\\Documents\\codelite_C++_projects\\OS_Semester-Project\\Instructions\\Program-File.txt");
	Ram *ram = new Ram();
	int queueCap = 6;
	PCB *readyQueue[queueCap];
	LongTermScheduler *LTscheduler = new LongTermScheduler(ram, PCBlist, disk, readyQueue, queueCap);
	CPU *cpu = new CPU(ram);
	Dispatcher *dispatcher =  new Dispatcher(cpu, LTscheduler, readyQueue, ram);
	
	
	while (!LTscheduler->done()){
		LTscheduler->loadProcesses();
		dispatcher->setCPU();
//		while(!cpu->isDone()){
//			cpu->decode();
//			cpu->isDone();
//		}
	}
}
