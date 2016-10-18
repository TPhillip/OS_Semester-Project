#include <string>
//#include "disk.h"
#include "PCB_list.h"
using namespace std;

class Loader{
public:
	Loader(PCB_list *setPCBlist, Disk *setdisk);
	Disk* getDisk() {return disk;}
	PCB_list* setPCB_list() { return PCBlist;}
	void readFile(string fname);
	unsigned int hex2dec(string hex);

private:
	string filename;
	Disk *disk;
	PCB_list *PCBlist;
};