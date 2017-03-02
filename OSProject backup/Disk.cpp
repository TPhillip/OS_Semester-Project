#include "Disk.h"


//using namespace std;
	
	//methods:
	//this method prints the amount of available space on the disk
	int Disk::available_space_on_disk()
	{
		int space = 2047 - current_index;
		std::cout<<"the available space on disk is: "<<space<<" words.";
		return space;
	}
	
	//this method returns the value stored in an index of the disk
	string Disk::get_from_Disk(int x)
	{
		string entry = DiskArray->at(x);
		return entry;
	}
	
	//this method writes to the next available index on the disk
	void Disk::add_to_disk(string adder)
	{
		if(is_full == true)
		{
			std::cout<<"Error, tried to write to disk, when disk is full."<<endl;
			return;
		}
		DiskArray->at(current_index) = adder;
		++current_index;
		if(current_index >= 2047)
		{
			is_full = true;
		}
		
	}

