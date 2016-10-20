#include "cpu.h"

CPU::CPU(Ram* setRam){
	ram = setRam;
	for(int i=0; i<16; i++){
		reg[i] = 0;
	}
}

CPU::~CPU(){
	
}

void CPU::set(int setJobID, int setOffset, int setInput, int setOutput, int setTemp, int setInputSize){
	jobID = setJobID;
	offset = setOffset;
	inputBuf = setInput;
	outputBuf = setOutput;
	tempBuf = setTemp;
	instruction = fetch(offset);
	pCount = 0;
	inputSize = setInputSize;
}

void CPU::decode(){
	instruction = hex2bin(instruction);
	string opcode = instruction.substr(2,6);
	string tempReg[4] = {0};		//reg[0] is always address, D-reg is reg[1]
	if(instruction.substr(0,2) == "00"){ //Arithmetic instruction
		tempReg[2] = instruction.substr(8,4); //s-reg
		tempReg[3] = instruction.substr(12,4);//s-reg
		tempReg[1] = instruction.substr(16,4);//d-reg
		tempReg[0] = instruction.substr(20,12);//addy
		execute(opcode, tempReg);
	} else if(instruction.substr(0,2) == "01"){ //Conditional Branch and Immediate instructoin
		tempReg[2] = instruction.substr(8,4);//b-reg
		tempReg[1] = instruction.substr(12,4);//d-reg
		tempReg[0] = instruction.substr(16,16);//addy
	} else if(instruction.substr(0,2) == "10"){ //Unconditional Jump instructoin
		tempReg[0] = instruction.substr(8,24);//addy
	} else if(instruction.substr(0,2) == "11"){ //Input and Output instruction
		tempReg[2] = instruction.substr(8,4);//reg1
		tempReg[1] = instruction.substr(12,4);//reg2
		tempReg[0] = instruction.substr(16,16);//addy
	} else{
		cout << "ERROR-------------------------------------------------------------------------" << endl;
	}
	
}

void CPU::execute(string opcode, string regs[]){
	int op = hex2dec(opcode);
	int intReg[4] = {0};
	for(int i = 0; i< 4; i++){
		intReg[i] = bin2dec(regs[i]);
	}
	switch(op)
	{
		case 0://00	
			reg[intReg[1]] = intReg[0];		 //read the contents of address into reg
			break;
		case 1://01
			break;
		case 2://02
		break;
		case 3://03
		break;
		case 4://04
		break;
		case 5://05
		break;
		case 6://06
		break;
		case 7://07
		break;
		case 8://08
		break;
		case 9://09
		break;
		case 10://0A
		break;
		case 11://0B
		break;
		case 12://0C
		break;
		case 13://0D
		break;
		case 14://0E
		break;
		case 15://0F
		break;
		case 16://10
		break;
		case 17://11
		break;
		case 18://12
		break;
		case 19://13
		break;
		case 20://14
		break;
		case 21://15
		break;
		case 22://16
		break;
		case 23://17
		break;
		case 24://18
		break;
		case 25://19
		break;
		case 26://1A
		break;
		
	}
}

string CPU::fetch(int index){
	string instruct = ram->get(index);
	return instruct;
}

string CPU::hex2bin(string sHex){
	transform(sHex.begin(), sHex.end(), sHex.begin(), ::tolower);
//	string temp = "";
	string sReturn = "";
	for (unsigned int i = 0; i < sHex.length(); ++i)
	{
//		temp = sReturn;
//		sReturn = "";
		switch (sHex[i])
		{
		case '0': sReturn.append("0000"); break;
		case '1': sReturn.append("0001"); break;
		case '2': sReturn.append("0010"); break;
		case '3': sReturn.append("0011"); break;
		case '4': sReturn.append("0100"); break;
		case '5': sReturn.append("0101"); break;
		case '6': sReturn.append("0110"); break;
		case '7': sReturn.append("0111"); break;
		case '8': sReturn.append("1000"); break;
		case '9': sReturn.append("1001"); break;
		case 'a': sReturn.append("1010"); break;
		case 'b': sReturn.append("1011"); break;
		case 'c': sReturn.append("1100"); break;
		case 'd': sReturn.append("1101"); break;
		case 'e': sReturn.append("1110"); break;
		case 'f': sReturn.append("1111"); break;
		}
//		temp.append(sReturn);
//		sReturn = temp;
//		temp = "";
	}
//	if (sReturn.length() < 32){
//		for(int j = sReturn.length(); j<32; j++){
//			temp = sReturn;
//			sReturn = "0";
//			sReturn.append(temp);
//			temp = "";
//		}
//	}
	
	return sReturn;
}

int CPU::hex2dec(string hex){
	double count = 0;
	int sum = 0;
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

int CPU::bin2dec(string bin){
	double count = 0;
	int sum = 0;
	double temp=0;
	for (int i=bin.length()-1; i>=0; i-=1){
		if(bin.substr(i,1)=="0"){
			temp = 0;
		}else{
			temp =1;
		}
		temp = temp*(pow(2, count));
		count +=1;
		sum += (unsigned int)temp;
	}
	return sum;
}

