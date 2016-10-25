#ifndef RAM_H
#define RAM_H
#include <string>
using namespace std;
class Ram
{
public:
	Ram();
	~Ram();
	void add(string entry);
	string get(int index)	{return ram[index];}
	void set(int index, string entry)	{ ram[index] = entry; }
	bool isFull();
	int getSize()	{ return size;}
	int getAvailable() { return capacity-size;}
	int getCap() {return capacity;}
	
private:
	int size;
	static const int capacity = 1024;
	string ram[capacity];

};

#endif // RAM_H
