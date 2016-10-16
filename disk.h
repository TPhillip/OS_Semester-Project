#include <string>
using namespace std;
class Disk{
public:
	Disk();

	void add(unsigned int entry);
	unsigned int get(int index);
	bool isFull();
	int getSize();
	
private:
	int size;
	static const int capacity = 2048;
	unsigned int disk[capacity];
};