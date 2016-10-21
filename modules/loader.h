#include <string>
#include "disk.h"
#include "PCB_list.h"
using namespace std;

class Loader{
public:
	Loader();
	Disk* getDisk();
	void setDisk(Disk *disk);
	void setPCBlist(PCB_list *PCBlist);
	void readFile(string fname);

private:
	string filename;
	Disk *disk;
	PCB_list *PCBlist;
};