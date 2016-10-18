#include <string>
//#include "disk.h"
#include "PCB_list.h"
using namespace std;

class Loader{
public:
	Loader();
	Disk* getDisk() {return disk;}
	PCB_list* setPCB_list() { return PCBlist;}
	void setDisk(Disk* setDisk) { disk = setDisk;}
	void setPCBlist(PCB_list* setPCBlist) {	PCBlist = setPCBlist;}
	void readFile(string fname);
	unsigned int hex2dec(string hex);

private:
	string filename;
	Disk *disk;
	PCB_list *PCBlist;
};