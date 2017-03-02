// Zane W. Gabriel K. Alex C. Tevin P.
#include "Scheduler.h"

//methods
	//this method runs all the sub methods, and is to be called in main.
	void Scheduler::run_scheduler()
	{
		check_for_completion();
	}
	
	//this method runs through the frame table looking for completed jobs. If they are completeed it prints there data and removes them from ram
	void Scheduler::check_for_completion()
	{
		for(PCB *cursor = PCB2; cursor !=NULL; cursor = cursor->get_link())
		{
			if (cursor->get_is_in_ram() && cursor->get_completed())
			{
				//this prints the contents of the Data for this finished process.
				//cout <<  << endl;
				outfile << "Process " << cursor->get_process_ID() << " finshed with Data values:\t";
				stat->logCompletion(cursor->get_process_ID());

				//uses pcb frame table to read ram
				//print instructions
				//print input buffer
				int startingJobpage = cursor->get_input_page() - cursor->get_instruct_page();
				int outputJobPage = cursor->get_page_count();
				int numJobs = cursor->get_input_buffer() + cursor->get_output_buffer() + cursor->get_temp_buffer();
				numJobs = (numJobs / 4)-1;
				int numJobsOne = numJobs;
				while (numJobsOne % 3 != 0 ) {
					++numJobsOne;
				}
				numJobs += startingJobpage;
				int increment = numJobsOne / 3;
				
				//string entry = ;
				//cout << entry << endl;
				outfile << "Hex\tbase10\tHex\tbase10\tHex\tbase10\tHex\tbase10\n";

				//cout << "1-12\t\t13-24\t\t25-36\t\t37-44" << endl;
				outfile << "1-12\t\t13-24\t\t25-36\t\t37-44\n";
				for (int k = 0; k < increment*3; ++k) {
					for (int i = startingJobpage + (k/4); i <= numJobs; i+=3) {
					//if (i < numJobs) {
					int frame = cursor->get_frame(i);
						if (frame == -1) {
							int page = cursor->get_disk_page(i);
							string hex = to_read_from->get_from_Disk(page * 4 + (k %4));
							//cout << hex << "    " << hex_to_base10(hex) << "\t";
							outfile << hex << "    " << hex_to_base10(hex) << "\t";
						}
						else {
							string hex = mmu->read_from_ram(frame, k%4);
							//cout << hex << "    " << hex_to_base10(hex) << "\t";
							outfile << hex << "    " << hex_to_base10(hex) << "\t";
						}
					}
					//cout << endl;
					outfile << "\n";
				}
				cursor->set_is_in_ram(false);
				cursor->set_is_running(false);
				mmu->clearFrames(cursor);
			}
		}	
	}
	//this method fills the unfilled frames with new processes
	void Scheduler::load_processes()
	{
		for (PCB *cursor = PCB2; cursor != NULL; cursor = cursor->get_link())
		{
			stat->logStart(cursor->get_process_ID());

			int free_frame = mmu->find_empty_frame();
			int instpage = cursor->get_instruct_page();
			cursor->set_first_instruct_ram(free_frame);
			cursor->set_req_page(0);
			mmu->service_page_fault(cursor);

			free_frame = mmu->find_empty_frame();
			int page = cursor->get_input_page() - instpage;
			cursor->set_first_input_ram(free_frame);
			cursor->set_req_page(page);
			mmu->service_page_fault(cursor);

			free_frame = mmu->find_empty_frame();
			cursor->set_first_output_ram(free_frame);
			page = cursor->get_output_page() - cursor->get_instruct_page();
			cursor->set_req_page(page);
			mmu->service_page_fault(cursor);

			free_frame = mmu->find_empty_frame();
			cursor->set_first_temp_ram(free_frame);
			page = cursor->get_temp_page() - cursor->get_instruct_page();
			cursor->set_req_page(page);
			mmu->service_page_fault(cursor);
			cursor->set_is_in_ram(true);
		}
	}
	
int Scheduler::hex_to_base10(string hex)
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
