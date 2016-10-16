#include "PCB_list.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

PCB_list::PCB_list()
{
	count=0;
	head = NULL;
	tail = NULL;
}

PCB_list::~PCB_list()
{
	delete[] head;
	delete[] tail;
}
void PCB_list::addPCB(int jobID, int numJobs, int priority){
	PCB *pcb =  new PCB(jobID, numJobs, priority);
	count+=1;
	if (head == NULL){
		head = pcb;
		tail = pcb;
	}else{
		PCB *temp;
		if(tail->getNext() == NULL){
			tail->setNext(pcb);
			temp = tail->getNext();
			temp->setPrev(tail);
			tail = temp;
		}else{
			while(tail->getNext() != NULL){
				tail = tail->getNext();
			}
			tail->setNext(pcb);
			temp = tail->getNext();
			temp->setPrev(tail);
			tail = temp;
		}
	}
	current = head;
}

void PCB_list::addJobInstruction(int jobID, int *jobInstructLocation){
	if(jobID == tail->getJobID()){
		tail->addJobInstructions(jobInstructLocation);
	}else{
		PCB *temp;
		temp = tail;
		bool proceed = true;
		while(proceed){
			if(temp->getNext() != NULL){
				temp = temp->getNext();
			}else{
				proceed = false;
			}
		}
		temp->addJobInstructions(jobInstructLocation);
	}
}
void PCB_list::addData(int jobID, int *data){
	if(jobID == tail->getJobID()){
		tail->addDataDisk(data);
	}else{
		PCB *temp;
		temp = tail;
		bool proceed = true;
		while(proceed){
			if(temp->getNext() != NULL){
				temp = temp->getNext();
			}else{
				proceed = false;
			}
		}
		temp->addDataDisk(data);
	}
}
void PCB_list::addBuffer(int setInput, int setOutput, int setTemp){
	tail->setBuffer(setInput, setOutput, setTemp);
}
void PCB_list::sortPriority(){
	PCB *temp1;
	temp1 = head;
	PCB *temp2;
	while(temp1->getNext() != NULL){
		 temp2 = head->getNext();
		if(temp1->getPriority()<temp2->getPriority()){
			placePrev(temp1, temp2);
		}else if(temp1->getPriority()<temp2->getPriority()){
			placeNext(temp1, temp2);
		}
	}
	current = head;
}
void PCB_list::placePrev(PCB *first, PCB *second){
	PCB  *prevFirst, *nextSec, *prevSec;
	prevFirst = first->getPrev();
	nextSec = second->getNext();
	prevSec = second->getPrev();
	first->setPrev(second);
	second->setPrev(prevFirst);
	second->setNext(first);
	prevSec->setNext(nextSec);
	nextSec->setPrev(prevSec);
	if(prevFirst==NULL){
		head = second;
	}
}
void PCB_list::placeNext(PCB *first, PCB *second){
	PCB  *nextFirst, *nextSec, *prevSec;
	prevSec = first->getPrev();
	nextFirst = second->getNext();
	nextSec = second->getPrev();
	first->setNext(second);
	second->setPrev(first);
	second->setNext(nextFirst);
	prevSec->setNext(nextSec);
}
void PCB_list::printPCBInfo(Disk *disk){
	PCB *temp;
		temp = head;
		temp->printPCB(disk);
		do{
			temp = temp->getNext();
			temp->printPCB(disk); 
		}while(temp->getNext() != NULL);
}

