// Zane W. Gabriel K. Alex C. Tevin P.
#ifndef PCB_H
#define PCB_H
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

//This class defines the program control block, which keeps track of data for eac process
class PCB
{
public:
	//constructor
	PCB(PCB* initial_link = NULL)
	{
		link = initial_link;
		page_table = new vector<Frame>;
		//clear cache and reg copies
		for (int i = 0; i < 4; ++i) {
			cache_copy[i] = new string[4];
		}
		cache_page_copy = new int[4];

		clear_cache_reg();


	}

	~PCB();

	// Member functions to set the data and link fields:
	void set_link(PCB* new_link) {
		link = new_link;
		hasNext = 1;
	}
	void set_process_ID(const int new_PID) { process_ID = new_PID; }
	void set_program_counter(const int new_value) { program_counter = new_value; }
	void set_first_instruct_ram(const int value) { first_instruct_ram = value; }
	void set_first_instruct_disk(const int value) { first_instruct_disk = value; }
	void set_length_instruct(const int value) { length_instruct = value; cache_copy[0]; }
	void set_first_data_ram(const int value) { first_data_ram = value; }
	void set_first_data_disk(const int value) { first_data_disk = value; }
	void set_length_data(const int value) { length_data = value; }
	void set_is_running(const bool value) { is_running = value; }
	void set_completed(const bool value) { completed = value; }
	void set_is_in_ram(const bool value) { in_ram = value; }
	void set_priority(const int value) { priority = value; }
	void set_job_length(const int value) { job_length = value; }
	void set_instruct_page(const int value) { instruct_location = value; }
	void no_Next() { hasNext = 0; }
	void set_input_buffer(const int value) { input_buffer = value; }
	void set_input_page(const int value) { input_location = value; }
	void set_output_buffer(const int value) { output_buffer = value; }
	void set_output_page(const int value) { output_location = value; }
	void set_temp_buffer(const int value) { temp_buffer = value; }
	void set_temp_page(const int value) { temp_location = value; }
	void set_faulty(const bool value) { page_fault = value; }
	// Constant member function to retrieve the current data:
	int get_process_ID( )const { return process_ID; }
	int get_program_counter( )const { return program_counter; }
	int get_first_instruct_ram( )const { return first_instruct_ram; }
	int get_first_instruct_disk( )const { return first_instruct_disk; }
	int get_length_instruct( )const { return length_instruct; }
	int get_first_data_ram( )const { return first_data_ram; }
	int get_first_data_disk( )const { return first_data_disk; }
	int get_length_data( )const { return length_data; }
	bool get_is_running()const{return is_running;}
	bool get_completed()const{return completed;}
	bool get_is_in_ram()const{return in_ram;}
	int get_priority()const { return priority; }
	int has_Next()const { return hasNext; }
	int get_job_length() const { return job_length; }
	int get_input_buffer()const { return input_buffer; }
	int get_instruct_page()const { return instruct_location; }
	int get_output_buffer()const { return output_buffer; }
	int get_output_page()const { return output_location; }
	int get_temp_buffer()const { return temp_buffer; }
	int get_temp_page()const { return temp_location; }
	string* get_cache_copy(int index) { return cache_copy[index]; }
	int* get_cache_page_copy() { return cache_page_copy; }
	int get_reg_copy(int a)const { return reg_copy[a]; }
	bool is_faulty()const { return page_fault; }
	int get_input_page()const { return input_location; }
	int get_page_count()const { return page_table->size()-1; }
	int get_frame(const int value) { return (&page_table->at(value))->frame; }
	void set_new_frame(const int value, const int pageNum);
	void set_new_page() { Frame *newFrame = new Frame(); page_table->push_back(*newFrame); }
	void set_first_input_ram(const int value) { first_input_ram = value; }
	void set_first_output_ram(const int value) { first_output_ram = value; }
	void set_first_temp_ram(const int value) { first_temp_ram = value; }
	void set_req_page(const int value) { req_index = value; }
	int get_req_page() { return req_index; }
	void set_page_valid(const bool value, int page) { (&page_table->at(page))->valid = value; }
	bool get_page_valid(const int page) { return (&page_table->at(page))->valid; }
	void set_disk_page(const int value, int page) { (&page_table->at(page))->diskPage = value; }
	int get_disk_page(const int page) {	return (&page_table->at(page))->diskPage;	}
	bool is_in_cache(const int page){ return (&page_table->at(page))->is_in_cache; }
	void set_in_cache(const bool value, int page){ (&page_table->at(page))->is_in_cache = value; }
	
	//function to retrun the current link
	PCB* get_link( ) const{ return link; }
	void clear_cache_reg();
	void set_reg_copy(int reg[16]);
	void set_cache_copy(string cache[4][4]);
	void set_cache_page_copy(int cache_page[4]);

	
	private:
			//this holds the location of the next process's PCB
		PCB* link;
		
		//this ID's the processs
		int process_ID=0;
		
		//this holds how many process have been run.
		int program_counter=0;
		
		//this holds the first instruction in RAM's location
		int first_instruct_ram=0;
		
		//this holds the first instruction in Disk's location
		int first_instruct_disk=0;
		
		//this holds the first data in RAM's location
		int first_data_ram=0;
		
		//this holds the first data in Disk's location
		int first_data_disk=0;
		
		//this holds the number of data elements
		int length_data=0;
		
		//this holds the number of instructions
		int length_instruct=0;
		
		//this shows wether or not a process is running on the cpu
		bool is_running = false;
		
		//this shows if the job is completed
		bool completed = false;
		
		//this shows wether or not something is in ram
		bool in_ram = false;


		int priority = 0;

		int hasNext = 0;

		int job_length = 0;
		int instruct_location = 0;
		int input_buffer = 0;
		int input_location = 0;
		int temp_buffer = 0;
		int temp_location = 0;
		int output_buffer = 0;
		int output_location = 0;
		string *cache_copy[4];
		int *cache_page_copy;
		int reg_copy[16];
		bool page_fault = false;
		struct Frame {
			int frame=-1;
			int diskPage = -1;
			bool valid=false;
			bool is_in_cache = false;
		};
		std::vector<Frame> *page_table;
		int first_input_ram = 0;
		int first_output_ram = 0;
		int first_temp_ram = 0;
		int req_index = 0;
};

#endif // PCB_H