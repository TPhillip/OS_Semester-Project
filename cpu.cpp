#include "cpu.h"

CPU::CPU(Ram* setRam){
	ram = setRam;
	for(int i=0; i<16; i++){
		cpuReg[i] = 0;
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
	done = false;
}

void CPU::decode(){
	instruction = hex2bin(instruction);
	string opcode = instruction.substr(2,6);
	string tempReg[4] = {0};		//reg[0] is always address, 
	int instructionType = 0;
	if(instruction.substr(0,2) == "00"){ //Arithmetic instruction
		tempReg[0] = instruction.substr(8,4); //s-reg
		tempReg[1] = instruction.substr(12,4);//s-reg
		tempReg[2] = instruction.substr(16,4);//d-reg
		tempReg[3] = instruction.substr(20,12);//addy
		instructionType = 0;
		execute(instructionType, opcode, tempReg);
	} else if(instruction.substr(0,2) == "01"){ //Conditional Branch and Immediate instructoin
		tempReg[0] = instruction.substr(8,4);//b-reg
		tempReg[1] = instruction.substr(12,4);//d-reg
		tempReg[2] = instruction.substr(16,16);//addy
		instructionType = 1;
		execute(instructionType, opcode, tempReg);
	} else if(instruction.substr(0,2) == "10"){ //Unconditional Jump instructoin
		tempReg[0] = instruction.substr(8,24);//addy
		instructionType = 2;
		execute(instructionType, opcode, tempReg);
	} else if(instruction.substr(0,2) == "11"){ //Input and Output instruction
		tempReg[0] = instruction.substr(8,4);//reg1 
		tempReg[1] = instruction.substr(12,4);//reg2 
		tempReg[2] = instruction.substr(16,16);//addy
		instructionType = 3;
		execute(instructionType, opcode, tempReg);
	} else{
		cout << "ERROR-------------------------------------------------------------------------" << endl;
	}
	
}

void CPU::execute(int instructionType, string opcode, string regs[]){
	int op = hex2dec(opcode);
	int intReg[4] = {0}; // 0 address, 1 d-reg, 2 s-reg, 3 s-reg

	//convert binarys strings to int for switch comparison
	for(int i = 0; i< 4; i++){
		intReg[i] = bin2dec(regs[i]);
	}
	switch(instructionType)
	{
		case 0:{	//Arithmetic instruction format
			//2 bits	6 bits 	4 bits 	4 bits 	4 bits	12 bits
			//00 		OPCODE 	S-reg 	S-reg 	D-reg 	000
			switch(op)
			{
				case 4:{//04		MOV 	R 	Transfers the content of one register into another
					//first two bits 00
					
					//EX Job 2 04020000
					//0000 0100 0000 0010 0000 0000 0000 0000
					//005C MOV R0 R2 // Moves the larger no. in reg-2 to accumulator
					
					//Ex Job 4 04300000
					//0000 0100 0011 0000 0000 0000 0000 0000
					//003C MOV R3 R0 // Moving the last number into reg-3
					
					//Ex Job 4 04230000
					//0000 0100 0010 0011 0000 0000 0000 0000
					//0038 MOV R2 R3 // Moving the last but one number into reg-2
					//int address = intReg[0];	//in number of bytes 
					int dReg = intReg[0];
					int sReg = intReg[1];
					//int s2Reg = intReg[2];
					//address = cpuReg[bReg];	//address is saved in b-reg
					//address = effectiveAddy(address);//gets the actual address	
					//int addressedData = hex2dec(fetch(address)); //retrieve contents in address of ram
					cpuReg[dReg]=cpuReg[sReg];
					decode();
					break;
					}
				case 5:{//05		ADD 	R 	Adds content of two S-regs into D-reg
						//first two bits 00
						//Ex Job 3 05070000
						//0000 0101 0000 0111 0000 0000 0000 0000
						//0040 ADD R0 R0 R7 // Add the content of accumulator with reg-7 and stored in acc.
						
						//Ex Job 4 05320000
						//0000 0101 0011 0010 0000 0000 0000 0000
						//0028 LOOP : ADD R0 R3 R2 // Find the next Fibonacci number
						
						int dReg = intReg[0];
						int s1Reg = intReg[1];
						int s2Reg = intReg[2];
						cpuReg[dReg]=cpuReg[s1Reg] + cpuReg[s2Reg];
						decode();
					break;
				}
				case 8:{//08		DIV 	R 	Divides content of two S-regs into D-reg
						//first two bits 00
						//Ex Job 3 08050000
						//0000 1000 0000 0101 0000 0000 0000 0000
						//0054 DIV R0 R0 R5 // Finding the average ,keeps in R0
						int dReg = intReg[0];
						int s1Reg = intReg[1];
						int s2Reg = intReg[2];
						cpuReg[dReg]= cpuReg[s1Reg] /cpuReg[s2Reg];
						decode();
					break;
				}
				case 16:{//10	SLT 	R 	Sets the D-reg to 1 if first S-reg is less than second B-reg, and 0 otherwise
						//first two bits 00
						//Ex job 4 10658000
						//0001 0000 0110 0101 1000 0000 0000 0000
						//0040 SLT R8 R6 R5 // Reg-8 is set to 1 ,if Reg6 < Reg5, and 0 otherwise
						int dReg = intReg[2];
						int s1Reg = intReg[0];
						int s2Reg = intReg[1];
						if(cpuReg[s1Reg]<cpuReg[s2Reg]){
							cpuReg[dReg] = 1;
						}else{
							cpuReg[dReg] = 0;
						}
						decode();
					break;
				}
			}
		}
		case 1:{		//Conditional Branch and Immediate format
				//2 bits	6 bits 	4 bits 	4 bits 	16 bits
				//01 		OPCODE 	B-reg 	D-reg 	Address
			switch(op)
			{
				case 2:{//02		ST 		I 	Stores content of address pointed to by cpu reg{bReg} into an address/cpu reg{dReg}
						//first two bits 01
						//Ex Job 1 42BD0000
						//0100 0010 1011 1101 0000 0000 0000 0000
						//0020 ST (R13) R11 // Store the data in the address pointed to by reg-13
					int dReg = intReg[1];
					int bReg = intReg[0];
					int address = intReg[2];
					if(dReg == 0){ 		//use address as destination
						address = effectiveAddy(address);
						int addressedData = hex2dec(fetch(address)); //find data to be written from source address.
						string entry = dec2hex(addressedData);
						ram->set(address, entry);
					}else{		//use content in bReg as address
						address = cpuReg[bReg];
						address = effectiveAddy(address); //gets the actual address	
						int addressedData = hex2dec(fetch(address)); //find data to be written from source address.
						cpuReg[dReg]=addressedData;
					}
					decode();
					break;
				}
				case 3:{//03		LW 		I 	Loads the content of an address into a reg.
						//first two bits 01
						//Ex Job 1 43970000
						//0100 0011 1001 0111 0000 0000 0000 0000
						//003C LOOP2: LW R7 0(R9) // Loads the content of the address in reg-9 in reg-7 , reg-9 is
																						// B-reg . 0 is the offset
					int address = intReg[2];	//in number of bytes 
					int dReg = intReg[1];
					int bReg = intReg[0];
					address = cpuReg[bReg];	//address is saved in b-reg
					address = effectiveAddy(address);//gets the actual address	
					int addressedData = hex2dec(fetch(address)); //retrieve contents in address of ram
					cpuReg[dReg]=addressedData;
					decode();
					break;
				}
				case 11:{//0B	MOVI 	I 	Transfers address/data directly into a register
						//first two bits 01
						//Ex Job 1 4B060000
						//0100 1011 0000 0110 0000 0000 0000 0000
						//0004 MOVI R6 0 // Set a counter to reg-6 and initialize to 0
						//Ex Job 1
						//0100 1011 0000 0001 0000 0000 0000 0000
						//0008 MOVI R1 0 // Set the Zero register to its value
						int address = intReg[2];	//in number of bytes 
						int dReg = intReg[1];
						int bReg = intReg[0];
						cpuReg[dReg] = bReg;
						decode();
					break;
				}
				case 12:{//0C	ADDI 	I 	Adds a data directly to the content of a register
						//first two bits 01
						//Ex Job 1 4C090004
						//0100 1100 0000 1001 0000 0000 0000 0100
						//0048 ADDI R9 4 // Incrementing the B-register by 4 bytes
						int address = intReg[2];	//in number of bytes 
						int dReg = intReg[1];
						int bReg = intReg[0];
						cpuReg[bReg] = cpuReg[bReg] + address;
						decode();
					break;
				}case 15:{//0F	LDI 	I 	Loads a data/address directly to the content of a register
						//first two bits 01
						//Ex Job 1 4F0A005C
						//0100 1111 0000 1010 0000 0000 0101 1100
						//0010 LDI R10 Inpt // Load address of input buffer into reg 10
						int address = intReg[2];	//in number of bytes 
						int dReg = intReg[1];
						int bReg = intReg[0];
						cpuReg[dReg] = address;
						decode();
					break;
				}
				case 21:{//15	BEQ 	I 	Branches to an address when content of B-reg = D-reg
						//first two bits 01
						//Ex Job 2 55810060
						//0101 0101 1000 0001 0000 0000 0110 0000
						//0058 BEQ R8 R1 LOOP2 // Branch if content of Reg- 8 and Reg-1 is equal
						//Ex 
						int address = intReg[2];	//in number of bytes 
						int dReg = intReg[1];
						int bReg = intReg[0];
						if(cpuReg[bReg] == cpuReg[dReg]){
							address = effectiveAddy(address);
							instruction = fetch(address);
						}
						decode();
					break;
				}
				case 22:{//16	BNE 	I 	Branches to an address when content of B-reg <> D-reg
						//first two bits 01
						//Ex Job 1 5681003C
						//0101 0110 1000 0001 0000 0000 0011 1100
						//0050 BNE R8 R1 LOOP2 // Branch if content of Reg- 8 and Reg-1 is not equal
						int address = intReg[2];	//in number of bytes 
						int dReg = intReg[1];
						int bReg = intReg[0];
						if(cpuReg[bReg] != cpuReg[dReg]){
							address = effectiveAddy(address);
							instruction = fetch(address);
						}
						decode();
					break;
				}
			}
		}
		case 2:{
			switch(op)
			{
				case 18:{//12	HLT 	J 	Logical end of program
					done = true;
					break;
				}
			}
		}
		case 3:{		//Input and Output instruction format
					//2 bits 	6 bits 	4 bits 	4 bit 	16 bits
					//11 		OPCODE 	Reg 1 	Reg 2 	Address
			switch(op)
			{
				case 0:{//00	RD	 I/O	 Reads content of I/P buffer into a accumulator
					//The instruction may read the content of Address/Reg 2 into Reg 1.
					//first two bits 11
					//Ex Job 1 C050005C
					//1100 0000 0101 0000 0000 0000 0101 1100
					int address = intReg[2];	//number of bytes
					int reg1 = intReg[0];
					int reg2 = intReg[1];
					if(reg2 ==0){	//reads the content of address in ram to cpu register{reg1}
						address = address/4;	//instructions are 4 bytes long.
						address = effectiveAddy(address); //gets the actual address
						int addressedData = hex2dec(fetch(address)); //retrieve contents in address of ram
						cpuReg[reg1] = addressedData;		 //read the contents of address into cpu register
						
					}else{	//reads teh content of cpu register{reg2} to cpu register{reg1}
						
						cpuReg[reg1] = cpuReg[reg2];//reads content of one cpu register to the other
					}
					decode();
					break;
				}
				case 1:{//01 	WR 	I/O 	Writes the content of accumulator into O/P buffer
						//The instruction may write the content of Reg 1 into a specified Address/Reg 2.
						//first two bits 11
						//Ex Job 1 C10000AC
						//1100 0001 0000 0000 0000 0000 1010 1100
						//0054 WR R0 Oupt // Write the content of the aacumulator into output buffer
					int address = intReg[2];	//in number of bytes 
					int reg1 = intReg[0];
					int reg2 = intReg[1];
					if(reg2 ==0){ 	//writes the content of cpu register {reg1} to address in ram
						address = effectiveAddy(address); //gets the actual address	
						string entry = dec2hex(cpuReg[reg1]);//convert contents of accumulator to hex string
						ram->set(address,entry);		 //writes the accumulator contents to ram
						
					}else{	//writes the content of cpu register{reg1} into cpu register {reg2}
						
						cpuReg[reg2] = cpuReg[reg1];//writes the content of one cpu register to the other
					}
					decode();
					break;
				}
			}
			break;
		}
	}
}
	//NOT USED
//	switch(op)
//	{	
//		
//		case 6://06		SUB 	R 	Subtracts content of two S-regs into D-reg
//		break;
//		case 7://07		MUL 	R 	Multiplies content of two S-regs into D-reg
//		break;
//		
//		case 9://09		AND 	R 	Logical AND of two S-regs into D-reg
//		break;
//		case 10://0A	OR 		R 	Logical OR of two S-regs into D-reg
//		break;
//		
//		
//		case 13://0D	MULI 	I 	Multiplies a data directly to the content of a register
//		break;
//		case 14://0E	DIVI 	I 	Divides a data directly to the content of a register
//		break;
//		
//		
//		case 17://11	SLTI 	I 	Sets the D-reg to 1 if first S-reg is less than a data, and 0 otherwise
//		break;
//
//		case 19://13	NOP 	- 	Does nothing and moves to next instruction
//		break;
//		case 20://14	JMP 	J 	Jumps to a specified location
//		break;
//		
//		
//		case 23://17	BEZ 	I 	Branches to an address when content of B-reg = 0
//		break;
//		case 24://18	BNZ 	I 	Branches to an address when content of B-reg <> 0
//		break;
//		case 25://19	BGZ 	I 	Branches to an address when content of B-reg > 0
//		break;
//		case 26://1A	BLZ 	I 	Branches to an address when content of B-reg < 0
//		break;
//		
//	}


int CPU::effectiveAddy(int address){
	int realAddy = (address/4) + offset;
	return realAddy;
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

string CPU::dec2hex(int dec){
	string hex = "";
	return hex;
	
}