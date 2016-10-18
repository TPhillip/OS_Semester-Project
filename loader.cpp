#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>
#include "loader.h"
#include "PCB_list.h"
using namespace std;

Loader::Loader(){
	//PCBlist = new PCB_list();
	//disk = new Disk();
}

void Loader::readFile(string fname){
	cout << "Reading file" << endl;
	filename = fname;
	cout << filename << endl;
	bool job;
	bool data;
	string line;
	int currentJobID = 0;
	ifstream programFile(fname.c_str());
	if(programFile.is_open()){
		while(getline(programFile, line)){
			if (line == "")
				continue;
						istringstream ssin(line);
			string lineArray[5];
			int count =0;
			if(line.substr(0,2)=="//"){
				while(ssin.good() && count<5){
					string temp = "";
					ssin >> temp;
					lineArray[count] = temp;
					count+=1;
				}
				if(lineArray[1]=="JOB"){
					job = true;
					data = false;
					int jobID =(int)hex2dec(lineArray[2]);
					int numJobs = (int)hex2dec(lineArray[3]);
					int priority = (int)hex2dec(lineArray[4]);
					currentJobID = jobID;
					PCBlist->addPCB(jobID, numJobs, priority);
				}else if(lineArray[1]=="Data"){
					data = true;
					job = false;
					int inbuffer = (int)hex2dec(lineArray[2]);
					int outBuffer = (int)hex2dec(lineArray[3]);
					int tempbuffer = (int)hex2dec(lineArray[4]);
					PCBlist->addBuffer(inbuffer, outBuffer, tempbuffer);
				}else if(lineArray[1]=="END"){
					data = false;
					job = false;
				}
			}else{
				int *location = new int;
				*location = disk->getSize();
				line = line.substr(2, line.length());
				disk->add(hex2dec(line));
				if(job){
					PCBlist->addJobInstruction(currentJobID, location);
				}else if(data){
					PCBlist->addData(currentJobID, location);
				}
			}
		}
		PCBlist->printPCBInfo(disk);
	}else{
		cout << "Program file did not open" << endl;
	}

}


unsigned int Loader::hex2dec(string hex){
	double count = 0;
	unsigned int sum = 0;
	for (int i=hex.length()-1; i>=0; i-=1){
		double temp = 0;
		if(hex.substr(i,1)=="0"){
			temp = 0;
		}else if(hex.substr(i,1)=="1"){
			temp = 1;
		}else if(hex.substr(i,1)=="2"){
			temp = 2;
		}else if(hex.substr(i,1)=="3"){
			temp = 3;
		}else if(hex.substr(i,1)=="4"){
			temp = 4;
		}else if(hex.substr(i,1)=="5"){
			temp = 5;
		}else if(hex.substr(i,1)=="6"){
			temp = 6;
		}else if(hex.substr(i,1)=="7"){
			temp = 7;
		}else if(hex.substr(i,1)=="8"){
			temp = 8;
		}else if(hex.substr(i,1)=="9"){
			temp = 9;
		}else if(hex.substr(i,1)=="A"){
			temp = 10;
		}else if(hex.substr(i,1)=="B"){
			temp = 11;
		}else if(hex.substr(i,1)=="C"){
			temp = 12;
		}else if(hex.substr(i,1)=="D"){
			temp = 13;
		}else if(hex.substr(i,1)=="E"){
			temp = 14;
		}else if(hex.substr(i,1)=="F"){
			temp = 15;
		}
		temp = temp*(pow(16, count));
		count+=1;
		sum+=(unsigned int)temp;
	}
	return sum;
}