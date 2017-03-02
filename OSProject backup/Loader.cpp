#include "Loader.h"

//methods 
//this method reads the file
void Loader::read_File()
{
	//cout << "0numInstructions\t" << num_instructions << endl;
	std::ifstream file(file_path);
	std::string line;
	bool is_instruct = true;
	int processNumber = 1, jobID, priorityNumber, jobLength;
	bool cont = true;
	while (std::getline(file, line) && cont)
	{
		//this loop will loop through the .txt and update pcb
		if (line.substr(0, 6) == "// JOB")
		{
			//parse the line into array to get jobID and priority
			istringstream ssin(line);
			string lineArray[5];
			int count = 0;
			while (ssin.good() && count < 5) {
				string temp = "";
				ssin >> temp;
				lineArray[count] = temp;
				++count;
			}
			priorityNumber = hex_to_base10(lineArray[4]);
			jobLength = hex_to_base10(lineArray[3]);
			jobID = hex_to_base10(lineArray[2]);
			if (processNumber != 1)
			{
				//exactly the same except checks for priority being either 0 (false) and 1 (true)
				PCB *PCB2 = new PCB();
				if (sortingAlgo == 2)
				{
					//with sjf sorting, we have to keep track of head pointer.
					//checks if job length of new job being loaded is less than the head pcb. 
					//Head pcb should have the lowest job length.
					if (head->get_length_instruct() >= jobLength) {
						PCB2->set_link(head);
						to_edit = PCB2;
						head = PCB2;
					}
					else {
						//compare the job length with the rest of the list
						bool set = false;
						to_edit = head;
						int count1 = 0;
						while (to_edit->has_Next() == 1) {
							// not needed, but kept just in case: 
							//to_edit->get_link()->get_program_counter());
							if (jobLength <= to_edit->get_link()->get_length_instruct())
							{
								if (to_edit->has_Next() == 1)
									PCB2->set_link(to_edit->get_link());
								to_edit->set_link(PCB2);
								to_edit = to_edit->get_link();
								to_edit->set_process_ID(jobID);
								to_edit->set_priority(priorityNumber);
								to_edit->set_job_length(jobLength);
								set = true;
								break;
							}
							if (to_edit->has_Next() == 1)
								to_edit = to_edit->get_link();
						}
						//if new job length is the highest, new pcb would not be set.
						//set new pcb as last which would be to_edit after traversal
						if (!set) {
							to_edit->set_link(PCB2);
							to_edit = to_edit->get_link();
						}
					}
				}
				else if (sortingAlgo == 1) {
					//with priority sorting, we have to keep track of head pointer.
					//checks if priority of new job being loaded is less than the head pcb. 
					//Head pcb should have the highest priority.
					if (priorityNumber >= head->get_priority()) {
						PCB2->set_link(head);
						to_edit = PCB2;
						head = PCB2;
					}
					else {
						//compare the priority with the rest of the list
						bool set = false;
						to_edit = head;
						int count1 = 0;
						while (to_edit->get_link() != NULL) {
							if (priorityNumber >= to_edit->get_link()->get_priority()) {
								if (to_edit->get_link() != NULL)
									PCB2->set_link(to_edit->get_link());
								to_edit->set_link(PCB2);
								to_edit = to_edit->get_link();
								to_edit->set_process_ID(jobID);
								to_edit->set_priority(priorityNumber);
								set = true;
								break;
							}
							if (to_edit->get_link() != NULL)
								to_edit = to_edit->get_link();
						}
						//if new priority is the lowest, new pcb would not be set.
						//set new pcb as last which would be to_edit after traversal
						if (!set) {
							to_edit->set_link(PCB2);
							to_edit = to_edit->get_link();
						}
					}
				}
				else {
					//continue as usual
					to_edit->set_link(PCB2);
					to_edit = to_edit->get_link();
				}
				while (num_instructions % 4 != 0) {
					++num_instructions;
				}
			}
			is_instruct = true;
			to_edit->set_process_ID(jobID);
			to_edit->set_priority(priorityNumber);
			to_edit->set_job_length(jobLength);
			processNumber++;
			to_edit->set_instruct_page(num_instructions/4);
		}
		//this branch runs if the value is data or instructions
		else if (line.substr(0, 2) == "0x")
		{
			if (is_instruct)
			{
				int diskPage = (num_instructions / 4);
				int offset = (num_instructions % 4);
				string temp = line.substr(2, 8);
				mmu->write_to_disk(diskPage, offset, temp);
				if (offset == 0) {
					to_edit->set_new_page();
					int current_page = diskPage - to_edit->get_instruct_page();
					to_edit->set_disk_page(diskPage, current_page);
				}
				temp = mmu->read_from_disk(diskPage, offset);
				to_edit->set_length_instruct(to_edit->get_length_instruct() + 1);
				++num_instructions;
				if (num_instructions == (to_edit->get_job_length() + to_edit->get_instruct_page() * 4)) {
					while (num_instructions % 4 != 0) {
						++num_instructions;
					}					
					to_edit->set_input_page(num_instructions/4);
				}
			}
			else if (!is_instruct)
			{
				int diskPage = num_instructions / 4;
				int offset = num_instructions % 4;
				mmu->write_to_disk(diskPage, offset, line.substr(2, 8));
				if (offset == 0) {
					to_edit->set_new_page();
					int current_page = diskPage - to_edit->get_instruct_page();
					to_edit->set_disk_page(diskPage, current_page);
				}
				to_edit->set_length_data(to_edit->get_length_data() + 1);
				++num_instructions;
				if (num_instructions == ((to_edit->get_input_page() * 4) + to_edit->get_input_buffer())) {
					to_edit->set_output_page(num_instructions/4);
				}
				else if (num_instructions == ((to_edit->get_output_page() * 4) + to_edit->get_output_buffer())) {
					to_edit->set_temp_page(num_instructions/4);
				}
			}
		}
		else if (line.substr(0, 7) == "// Data")
		{
			//parse the line into array to get jobID and priority
			istringstream ssin(line);
			string lineArray[5];
			int count = 0;
			while (ssin.good() && count < 5) {
				string temp = "";
				ssin >> temp;
				lineArray[count] = temp;
				++count;
			}
			int tempBuffer = hex_to_base10(lineArray[4]);
			int outputBuffer = hex_to_base10(lineArray[3]);
			int inputBuffer = hex_to_base10(lineArray[2]);
			is_instruct = false;
			to_edit->set_first_data_disk(num_instructions/4);
			to_edit->set_temp_buffer(tempBuffer);
			to_edit->set_output_buffer(outputBuffer);
			to_edit->set_input_buffer(inputBuffer);
		}
	}
	to_edit = head;
	if (sortingAlgo == 0)
	{
		outfile << "List of Processes (FIFO)" << endl;
		while (to_edit != NULL) {
			outfile << "job\t" << to_edit->get_process_ID() << "\t" << "priority\t" << to_edit->get_priority() << "\t" << "Length " << to_edit->get_length_instruct() << endl;
			to_edit = to_edit->get_link();
		}
	}
	if (sortingAlgo == 1)
	{
		outfile << "List of Processes sorted by priority" << endl;
		while (to_edit != NULL) {
			outfile << "job\t" << to_edit->get_process_ID() << "\t" << "priority\t" << to_edit->get_priority() << "\t" << "Length " << to_edit->get_length_instruct() << endl;
			to_edit = to_edit->get_link();
		}
		
	}

	if (sortingAlgo == 2)
	{
		outfile << "Sorted list based on SJF" << endl;
		while (to_edit->has_Next() == 1) {
			outfile << "job " << to_edit->get_process_ID() << "\t" << "priority\t" << to_edit->get_priority() << "\tLength\t " << to_edit->get_length_instruct() << endl;
			to_edit = to_edit->get_link();
		}
	}
	outfile << endl;
	outfile.close();
}
int Loader::hex_to_base10(string hex)
{
	double count = 0;
	int sum = 0;
	for (int i = hex.length() - 1; i >= 0; i -= 1)
	{
		double temp = 0;
		if (hex.substr(i, 1) == "0")
		{
			temp = 0;
		}
		else if (hex.substr(i, 1) == "1")
		{
			temp = 1;
		}
		else if (hex.substr(i, 1) == "2")
		{
			temp = 2;
		}
		else if (hex.substr(i, 1) == "3")
		{
			temp = 3;
		}
		else if (hex.substr(i, 1) == "4")
		{
			temp = 4;
		}
		else if (hex.substr(i, 1) == "5")
		{
			temp = 5;
		}
		else if (hex.substr(i, 1) == "6")
		{
			temp = 6;
		}
		else if (hex.substr(i, 1) == "7")
		{
			temp = 7;
		}
		else if (hex.substr(i, 1) == "8")
		{
			temp = 8;
		}
		else if (hex.substr(i, 1) == "9")
		{
			temp = 9;
		}
		else if (hex.substr(i, 1) == "A")
		{
			temp = 10;
		}
		else if (hex.substr(i, 1) == "B")
		{
			temp = 11;
		}
		else if (hex.substr(i, 1) == "C")
		{
			temp = 12;
		}
		else if (hex.substr(i, 1) == "D")
		{
			temp = 13;
		}
		else if (hex.substr(i, 1) == "E")
		{
			temp = 14;
		}
		else if (hex.substr(i, 1) == "F")
		{
			temp = 15;
		}
		else if (hex.substr(i, 1) == "a")
		{
			temp = 10;
		}
		else if (hex.substr(i, 1) == "b")
		{
			temp = 11;
		}
		else if (hex.substr(i, 1) == "c")
		{
			temp = 12;
		}
		else if (hex.substr(i, 1) == "d")
		{
			temp = 13;
		}
		else if (hex.substr(i, 1) == "e")
		{
			temp = 14;
		}
		else if (hex.substr(i, 1) == "f")
		{
			temp = 15;
		}
		temp = temp * (pow(16, count));
		count += 1;
		sum += (int)temp;
	}
	return sum;
}