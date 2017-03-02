#include "RAM.h"
#include <string>
#include <sstream>
#include <iostream>

//methods:
	//this method returns the value stored in an index of the disk
	string RAM::get_from_RAM(int x)
	{
		return RAMArray[x];
	}
	
	//this method writes to the next available index on the disk
	void RAM::add_to_RAM(int x, string adder)
	{
		if(x > 1024)
		{
			std::cout<<"Error, tried to write to a non-existing memory location."<<endl;
			return;
		}
		RAMArray[x] = adder;
		
	}

