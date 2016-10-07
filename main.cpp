#include <iostream>
//#include <tables.h>
#include "modules/disk.h"
#include "modules/loader.h"
#include "modules/scheduler.h"
#include "modules/dispatcher.h"
#include "modules/cpu.h"

using namespace std;

int main(){
	//loader(); //loads all off given file into simulated disk
	while(true){
		//scheduler();  //  take processes from disk and insert fully into simulated . . .	.                        ram, as well as remove finished processes
		//dispatcher(); //fetches values from ram, converts to binary, sends to cpu 
		//CPU(); //executes
		//waitforinterrupt();   //waits for cpu to be done
	}
	return 0;
}