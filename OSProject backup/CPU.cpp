// Zane W. Gabriel K. Alex C. Tevin P.
#include "CPU.h"

void CPU::set_to_run(int start_index, PCB *PCBlist)
{
	starting_RAM_Location = 0;
	given_start = true;
	done = false;
	//decode();
	PCB2 = PCBlist;
	instruction_type =0;
	page_fault = false;
	done = false;
	input_buffer = PCB2->get_job_length() + PCB2->get_job_length() % 4;
	output_buffer = input_buffer + PCB2->get_output_buffer() + PCB2->get_output_buffer() % 4;
	temp_buffer = output_buffer + PCB2->get_temp_buffer() + PCB2->get_temp_buffer() % 4;
	max_instructs = PCB2->get_job_length()-1;
	max_input = max_instructs + PCB2->get_input_buffer();
	max_output = max_input + PCB2->get_output_buffer();
	max_temp= max_output + PCB2->get_temp_buffer();
	set_reg_copy();
	set_cache_copy();
	set_cache_page_copy();
}

int CPU::effective_addy(int address)
{

	int realAddy = address/4;
	int numJobs = max_instructs;
	
	if (realAddy > numJobs) {
		realAddy -= numJobs;
		while ((numJobs+1) % 4 != 0) {
			++numJobs;
		}
		realAddy = realAddy + numJobs;
	}
	return realAddy;
}
void CPU::printReg(){
	for(int i=0; i< 16; i++){
		cout << "cpu register " << i << "\t" << cpuReg[i] << endl;
	}	
}
void CPU::clear_cache() {
	
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
				cache[i][j] = "";
		}
	}
	for (int i = 0; i < 16; ++i) {
		cpuReg[i] = 0;
	}
}
//checks to see if a value is in cache
bool CPU::check_cache(int page) {
	bool found = false;
	int cache_number = cache_address(page);
	if (cache_page[cache_number] == page) {
		found = true;
	}
	if (PCB2->is_in_cache(page)) {
		found = true;
	}
	if (!found) {
		if (!PCB2->get_page_valid(page)) {
			page_fault = true;
			PCB2->set_faulty(page_fault);
			PCB2->set_req_page(page);
		}
		else {
			load_cache(page);
			found = true;
		}
	}
	return found;
}
//Loads cache. only called when process starts processing and when cache is out.
void CPU::load_cache(int page) {
	int max;
	int cache_number = cache_address(page);
	string location = to_string(page);
	int oldPage = cache_page[cache_number];		
	int frame = PCB2->get_frame(page);
	for (int i = 0; i < 4; ++i) {
		string temp;
		while (!mmu->is_busy()) {
			mmu->set_busy(true);
			temp = mmu->read_from_ram(frame, i);
			mmu->set_busy(false);
			break;
		}

		cache[cache_number][i] = temp;
	}
	cache_page[cache_number] = page;
	if (oldPage != -1) {
		PCB2->set_in_cache(false, oldPage);
	}
	PCB2->set_in_cache(true, page);
}
string CPU::fetch(int program_index) {
	string return_instruct = "";	
	int page = get_page(program_index);
	int offset = program_index % 4;
	int cache_number = cache_address(page);
	bool in_cache = check_cache(page);
	if (in_cache) {
			string address = cache[cache_number][offset];
			return address;
	}
	return return_instruct;
}
void CPU::set_cache( int program_index, string entry)	{
	bool proceed = false;
	int page = get_page(program_index);
	int offset = program_index % 4;
	int cache_number = cache_address(page);
	bool in_cache = check_cache(page);
	if(in_cache){
		cache[cache_number][offset] = entry;
		while (!mmu->is_busy()) {
			mmu->set_busy(true);
			mmu->write_to_ram(page, offset, entry, PCB2);
			mmu->set_busy(false);
			break;
		}
	}
}
int CPU::cache_address(int page) {

	int cache_number = 0;
	//uses disk page to calculate
	page = page + PCB2->get_instruct_page();
	if(page >= PCB2->get_instruct_page() && page < PCB2->get_input_page())
		cache_number = 0;
	else if(page >= PCB2->get_input_page() && page < PCB2->get_output_page())
		cache_number = 1;
	else if (page >= PCB2->get_output_page() && page < PCB2->get_temp_page())
		cache_number = 2;
	else 
		cache_number = 3;
	return cache_number;


}
int CPU::get_page(int program_index) {
	int page = program_index / 4;
	return page;
}
void CPU::set_reg_copy() {
	for (int i = 0; i < 16; ++i) {
		cpuReg[i] = PCB2->get_reg_copy(i);
	}
}
void CPU::set_cache_copy() {
	for (int i = 0; i < 4; ++i) {
		string *cache_copy = PCB2->get_cache_copy(i);
		for (int j = 0; j < 4; ++j) {
				cache[i][j] = cache_copy[j];
		}
	}
}
void CPU::set_cache_page_copy() {
	int *cache_page_copy = PCB2->get_cache_page_copy();
	for (int i = 0; i < 4; ++i) {
		cache_page[i] = cache_page_copy[i];
	}
}
void CPU::decode_and_execute()
{
	page_fault = false;
	temp_stat = stat->procPunchIn();
	int next_instruct = PCB2->get_program_counter();
	int current_page = get_page(next_instruct);
	string instruct = "";
	bool proceed = false;
	bool in_cache = check_cache(current_page);
	if (in_cache){
		instruct = fetch(next_instruct);
		string binary = hex_to_bin(instruct);
		int inst_type = bin_to_base10(binary.substr(0, 2));
		instruction_type = inst_type;
		string op = binary.substr(2, 6);
		opcode = op;
		if (instruction_type == 0)
		{
			//arithmetic: 2bits = indicator, 6bits = opcode, 4bits = S-reg1,  4bits = s-reg2, 4bits = d-reg, 12bits = not used(000000)
			bin_instructions[0] = binary.substr(8, 4);
			bin_instructions[1] = binary.substr(12, 4);
			bin_instructions[2] = binary.substr(16, 4);
		}
		else if (instruction_type == 1)
		{
			//Conditional branch and Immediate: 2bits = indicator, 6bits = opcode, 4bits = b-reg1,  4bits = d-reg2, 16bits = address)
			bin_instructions[0] = binary.substr(8, 4);
			bin_instructions[1] = binary.substr(12, 4);
			bin_instructions[2] = binary.substr(16, 16);
		}
		else if (instruction_type == 2)
		{
			//unconditional jump: 2bits = indicator, 6bits = opcode, 24bits = address)
			bin_instructions[0] = binary.substr(8, 24);
		}
		else if (instruction_type == 3)
		{
			//Input/output: 2bits = indicator, 6bits = opcode, 4bits = reg1,  4bits = reg2, 16bits = address)
			bin_instructions[0] = binary.substr(8, 4);
			bin_instructions[1] = binary.substr(12, 4);
			bin_instructions[2] = binary.substr(16, 16);
		}
		else {
			cout << "incorrect binary string" << endl;
		}
		execute();
	}
	stat->incCpuCycles(PCB2->get_process_ID());
	if (page_fault) {
		stat->incPageFaults(PCB2->get_process_ID());
		PCB2->set_is_running(false);
		PCB2->set_cache_copy(cache);
		PCB2->set_reg_copy(cpuReg);
		PCB2->set_cache_page_copy(cache_page);
		clear_cache();
	}
	
}
void CPU::execute(){
	int op = bin_to_base10(opcode);
	int intReg[4] = {0}; // 0 address, 1 d-reg, 2 s-reg, 3 s-reg
	//convert binarys strings to int for switch comparison
	for(int i = 0; i< 4; i++){
		intReg[i] = bin_to_base10(bin_instructions[i]);
	}
	int starting_prog_counter = PCB2->get_program_counter();
	switch(instruction_type)
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
					int dReg = intReg[0];
					int sReg = intReg[1];
					cpuReg[dReg]=cpuReg[sReg];
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
						
						int dReg = intReg[2];
						int s1Reg = intReg[0];
						int s2Reg = intReg[1];
						cpuReg[dReg]=cpuReg[s1Reg] + cpuReg[s2Reg];
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
						cpuReg[dReg]= cpuReg[s2Reg] /cpuReg[s1Reg];
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
					if(dReg != 0){		//use content in bReg as address
						address = cpuReg[dReg];
					}
					int page = get_page(address);
					address = effective_addy(address);
					int offset = address;
					string entry = base10_to_hex(cpuReg[bReg]);
					set_cache(address, entry);
					if (!page_fault) {
						stat->logIoWR(PCB2->get_process_ID());
					}
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
					address = effective_addy(address);//gets the actual address	
					int page = get_page(address);
					bool in_cache = check_cache(page);
					if (in_cache) {
						int addressedData = hex_to_base10(fetch(address)); //retrieve contents in address of ram
						cpuReg[dReg] = addressedData;
					}

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
						cpuReg[dReg] = address;
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
						cpuReg[dReg] += address;
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
							PCB2->set_program_counter(address/4);
						}
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
							PCB2->set_program_counter(address/4);
						}
					break;
				}
			}
		}
		case 2:{
			switch(op)
			{
				case 18:{//12	HLT 	J 	Logical end of program
					for (int j=0; j<16; j++){
						cpuReg[j]=0;
					}
					PCB2->set_completed(true);
					PCB2->set_is_running(false);
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
					if (PCB2->get_program_counter() == 7) {
						int n=4;
					}
					int address = intReg[2];	//number of bytes
					int reg1 = intReg[0];
					int reg2 = intReg[1];
					if(reg2 ==0){	//reads the content of address in ram to cpu register{reg1}
						//address = address/4;	//instructions are 4 bytes long.
						address = effective_addy(address); //gets the actual address
					}else{	//reads teh content of cpu register{reg2} to cpu register{reg1}
						address=effective_addy(cpuReg[reg2]);
					}
					int page = get_page(address);
					bool in_cache = check_cache(page);
					if (in_cache){
						int addressedData = hex_to_base10(fetch(address)); //retrieve contents in address of ram
						cpuReg[reg1] = addressedData;		 //read the contents of address into cpu register
						stat->logIoRD(PCB2->get_process_ID());
						if (addressedData == 44) {
							int n = 4;
						}
					}
					else {
					}
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
					if(reg2 !=0){ //writes the content of cpu register{reg1} into address stored in cpu register {reg2}
						address = cpuReg[reg2];
					}
					address = effective_addy(address); //gets the actual address	
					string entry = base10_to_hex(cpuReg[reg1]);//convert contents of reg1 to hex string
					//writes the reg1 contents to ram
					int page = get_page(address);
					set_cache(address, entry);
					if (!page_fault) {
						stat->logIoWR(PCB2->get_process_ID());
					}
					break;
				}
			}
			break;
		}
	}
	int ending_prog_counter = PCB2->get_program_counter();
	if (!page_fault) {
		//if program counter has not been changed by branch or other jump method
		if (!done) {
			if (starting_prog_counter - ending_prog_counter == 0) {
				PCB2->set_program_counter(PCB2->get_program_counter() + 1);
			}
		}
	}
	stat->procPunchOut(PCB2->get_process_ID(), temp_stat);
}



string CPU::base10_to_hex(int decimalNumber){
	string hex = "", temp2="";
	int quotient;
	int i=0,j,temp,k;
	char hexadecimalNumber[100];
	quotient = decimalNumber;

	while(quotient!=0)
	{
		temp = quotient % 16;

      //To convert integer into character
		if( temp < 10)
			temp =temp + 48;
		else
			temp = temp + 55;
			
		hexadecimalNumber[i++]= temp;
		quotient = quotient / 16;
	}

    for(j = i -1 ;j>= 0;j--){
		hex += hexadecimalNumber[j];
	}
	for(k = 0; k<(8-hex.length()); k++){
		temp2 += "0";
	}
	temp2+=hex;
	hex=temp2;
	return hex;
}

string CPU::Base10_to_bin(int n)
{
    int size=sizeof(n)*8;
    string binary;
    bool s=0;
    for (int a=0;a<size;a++){
        bool bit=n>>(size-1);
        if (bit)
            s=1;
        if (s)
            binary.push_back(bit+'0');
        n<<=1;
    }
    if (!binary.size())
        binary.push_back('0');
    return binary;
}


int CPU::bin_to_base10(string bin)
{
	double count = 0;
	int sum = 0;
	double temp=0;
	for (int i=bin.length()-1; i>=0; i-=1)
	{
		if(bin.substr(i,1)=="0")
		{
			temp = 0;
		}
		else
		{
			temp = 1;
		}
		temp = temp*(pow(2, count));
		count +=1;
		sum += (unsigned int)temp;
	}
	return sum;
}

int CPU::hex_to_base10(string hex)
{
	double count = 0;
	int sum = 0;
	for (int i=hex.length()-1; i>=0; i-=1)
	{
		double temp = 0;
		if(hex.substr(i,1)=="0")
		{
			temp = 0;
		}
		else if(hex.substr(i,1)=="1")
		{
			temp = 1;
		}
		else if(hex.substr(i,1)=="2")
		{
			temp = 2;
		}
		else if(hex.substr(i,1)=="3")
		{
			temp = 3;
		}
		else if(hex.substr(i,1)=="4")
		{
			temp = 4;
		}
		else if(hex.substr(i,1)=="5")
		{
			temp = 5;
		}
		else if(hex.substr(i,1)=="6")
		{
			temp = 6;
		}
		else if(hex.substr(i,1)=="7")
		{
			temp = 7;
		}
		else if(hex.substr(i,1)=="8")
		{
			temp = 8;
		}
		else if(hex.substr(i,1)=="9")
		{
			temp = 9;
		}
		else if(hex.substr(i,1)=="A")
		{
			temp = 10;
		}
		else if(hex.substr(i,1)=="B")
		{
			temp = 11;
		}
		else if(hex.substr(i,1)=="C")
		{
			temp = 12;
		}
		else if(hex.substr(i,1)=="D")
		{
			temp = 13;
		}
		else if(hex.substr(i,1)=="E")
		{
			temp = 14;
		}
		else if(hex.substr(i,1)=="F")
		{
			temp = 15;
		}
		else if(hex.substr(i,1)=="a")
		{
			temp = 10;
		}
		else if(hex.substr(i,1)=="b")
		{
			temp = 11;
		}
		else if(hex.substr(i,1)=="c")
		{
			temp = 12;
		}
		else if(hex.substr(i,1)=="d")
		{
			temp = 13;
		}
		else if(hex.substr(i,1)=="e")
		{
			temp = 14;
		}
		else if(hex.substr(i,1)=="f")
		{
			temp = 15;
		}
		temp = temp*(pow(16, count));
		count+=1;
		sum+=(unsigned int)temp;
	}
	return sum;
}

string CPU::hex_to_bin(string sHex)
{
	string sReturn = "";
	for (unsigned int i = 0; i < sHex.length(); ++i)
	{
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
		case 'A': sReturn.append("1010"); break;
		case 'b': sReturn.append("1011"); break;
		case 'B': sReturn.append("1011"); break;
		case 'c': sReturn.append("1100"); break;
		case 'C': sReturn.append("1100"); break;
		case 'd': sReturn.append("1101"); break;
		case 'D': sReturn.append("1101"); break;
		case 'e': sReturn.append("1110"); break;
		case 'E': sReturn.append("1110"); break;
		case 'f': sReturn.append("1111"); break;
		case 'F': sReturn.append("1111"); break;
		}
	}
	return sReturn;
}

string CPU::bin_to_hex(string sBin)
{
	string hex ="";
	
	
	
	
	return hex;
}
