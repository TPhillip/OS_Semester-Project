#ifndef RAM_H
#define RAM_H

class Ram
{
public:
	Ram();
	~Ram();
	void add(unsigned int entry);
	unsigned int get(int index)	{return ram[index];}
	bool isFull();
	int getSize()	{ return size;}
	int getAvailable() { return capacity-size;}
	int getCap() {return capacity;}
	
private:
	int size;
	static const int capacity = 1024;
	unsigned int ram[capacity];

};

#endif // RAM_H
