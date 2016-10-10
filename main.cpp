#include <iostream>

#include "modules/disk.h"
#include "modules/loader.h"

using namespace std;

Loader loader; //loads all off given file into simulated disk

int main(){
	loader.readFile("instructions/Program-File.txt");
	return 0;
	while(true){
		//scheduler();  //  take processes from disk and insert fully into simulated . . .	.                        ram, as well as remove finished processes
		//dispatcher(); //fetches values from ram, converts to binary, sends to cpu 
		//CPU(); //executes
		//waitforinterrupt();   //waits for cpu to be done
	}
	return 0;
}