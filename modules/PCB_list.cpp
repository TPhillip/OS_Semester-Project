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
	current = NULL;
}

PCB_list::~PCB_list()
{
}
void PCB_list::addPCB(string *jobID){
	PCB *pcb =  new PCB();
	pcb->setJobID(jobID);
	if (head == NULL){
		head = pcb;
		count+=1;
		current = pcb;
	}else{
		PCB *temp;
		if(current->getNext() == NULL){
			current->setNext(pcb);
			current = current->getNext();
		}else{
			while(current->getNext() != NULL){
				current = current->getNext();
			}
			current->setNext(pcb);
			count+=1;
		}
	}
}
int PCB_list::countPCB(){
	 return 0;
}
void PCB_list::addJobInstruction(string *jobID, int *jobInstructLocation){
	if(jobID == current->getJobID()){
		current->addJobInstructions(jobInstructLocation);
	}else{
		PCB *temp;
		temp = current;
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
void PCB_list::addData(string *jobID, int *data){
	if(jobID == current->getJobID()){
		current->addDataDisk(data);
	}else{
		PCB *temp;
		temp = current;
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
void PCB_list::printPCBInfo(){
	PCB *temp;
		temp = head;
		temp->printPCB();
		do{
			temp = temp->getNext();
			temp->printPCB(); 
		}while(temp->getNext() != NULL);
}

