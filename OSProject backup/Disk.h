#ifndef DISK_H
#define DISK_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

//This class defines the disk, which entails an array of size 2048, where each element holds a word of 8 hex characters.
class Disk
{
public:
	Disk(){
		DiskArray = new vector<string>;
		for (int i = 0; i < 2048; ++i) {
			string temp = "";
			DiskArray->push_back(temp);
		}
	};
	~Disk(){};

	
	//this method prints the amount of available space on the disk
	int available_space_on_disk();
	
	//this method returns the value stored in an index of the disk
	string get_from_Disk(int x);

	//this method writes to the next available index on the disk
	void add_to_disk(string adder);

	void set(int index, string entry) { DiskArray->at(index) = entry; }
private:

	std::vector<string> *DiskArray;
	string DiskArray2[2048];
	int current_index = 0;
	bool is_full = false;
};

#endif // DISK_H
