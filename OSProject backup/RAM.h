#ifndef RAM_H
#define RAM_H

#include <string>
using namespace std;

//This class defines the RAM, which entails an array of size 1024, where each element holds a word of 8 hex characters. 
//Only these method can access or write to memory 
class RAM
{
public:
	RAM(){};
	~RAM(){};
	
	string RAMArray[1024];
	
	//this method returns the value stored in an index of the disk
	string get_from_RAM(int x);

	//this method writes to the next available index on the disk
	void add_to_RAM(int x, string adder);
	
	void set(int index, string entry)	{ RAMArray[index] = entry; }
	bool is_full();
private:
	bool full = false;
	
};


#endif // RAM_H
