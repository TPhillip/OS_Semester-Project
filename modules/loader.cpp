#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "loader.h"
#include "PCB_list.h"
using namespace std;

Loader::Loader(){
	PCBlist = new PCB_list();
	disk = new Disk();
}

void Loader::readFile(string fname){
	cout << "Reading file" << endl;
	filename = fname;
	cout << filename << endl;
	bool job;
	bool data;
	string *line = new string;
	string *currentJobID = new string;
	ifstream programFile(fname.c_str());
	if(programFile.is_open()){
		while(getline(programFile, *line)){
			istringstream ssin(*line);
			string *lineArray[5];
			*lineArray = new string[5];
			int *count=new int;
			*count = 0;
			cout << line << endl;
			if(line->substr(0,2)=="//"){
				while(ssin.good() && *count<5){
					string *temp = new string;
					ssin >> *temp;
					lineArray[*count] = temp;
					*count+=1;
				}
				if(*lineArray[1]=="JOB"){
					job = true;
					data = false;
					string *jobID = new string();
					jobID = lineArray[2];
					*currentJobID = *jobID;
					PCBlist->addPCB(jobID);
				}else if(*lineArray[1]=="Data"){
					data = true;
					job = false;
				}else if(*lineArray[1]=="END"){
					data = false;
					job = false;
				}
			}else{
				int *location = new int;
				location = disk->getSize();
				string *entry = new string;
				*entry = *line;
				disk->add(entry);
				if(job){
					PCBlist->addJobInstruction(currentJobID, location);
				}else if(data){
					PCBlist->addData(currentJobID, location);
				}
			}
		}
		PCBlist->printPCBInfo();
	}else{
		cout << "Program file did not open" << endl;
	}

}

Disk* Loader::getDisk(){
	return disk;
}

void Loader::setDisk(Disk *disk){
	this->disk = disk;
}

void Loader::setPCBlist(PCB_list *PCBlist){
	this->PCBlist = PCBlist;
}