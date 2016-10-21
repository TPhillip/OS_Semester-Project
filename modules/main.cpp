#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "modules\loader.h"


int main(int argc, char **argv)
{
	Disk *disk = new Disk();
	PCB_list *PCBlist = new PCB_list();
	Loader *loader = new Loader();
	loader->setPCBlist(PCBlist);
	loader->setDisk(disk);
	loader->readFile("C:\\Users\\gkigu\\OneDrive\\Documents\\codelite_C++_projects\\OS_Semester-Project\\Instructions\\Program-File.txt");
}
