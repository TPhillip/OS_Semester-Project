#ifndef PCB_LIST_H
#define PCB_LIST_H
#include "PCB.h"
#include <stddef.h>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
using namespace std;
class PCB_list
{
public:
	PCB_list();
	~PCB_list();
	void addPCB(string *jobID);
	int countPCB();
	void addJobInstruction(string *jobID, int *jobInstructLocation);
	void addData(string *jobID, int *data);
	void printPCBInfo();
	
private:
	PCB *head;
	PCB *current;
	int count;
};

#endif // PCB_LIST_H
