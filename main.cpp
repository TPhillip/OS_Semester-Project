#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "modules\loader.h"
#include "modules\LongTermScheduler.h"


int main(int argc, char **argv)
{
		for(int i=0; i<30; i= i+1){
////		//LTscheduler.loadProcesses(priority);
	}
	//Disk *disk2 = new Disk();
	//PCB_list *PCBlist = new PCB_list();
	//Loader *loader = new Loader();
	Loader loader;
	//loader->setPCBlist(PCBlist);
	//loader->setDisk(disk2);
	loader.readFile("C:\\Users\\gkigu\\OneDrive\\Documents\\codelite_C++_projects\\OS_Semester-Project\\Instructions\\Program-File.txt");
	
	LongTermScheduler LTscheduler;
	PCB_list *PCBlist = loader.getPCB_list();
	LTscheduler.setPCB_list(PCBlist);
	bool priority = false;
	//PCB* pcb=PCBlist->getHeadPtr();
//	i->printPCB(loader.getDisk());
	int count = PCBlist->countPCB();

}
