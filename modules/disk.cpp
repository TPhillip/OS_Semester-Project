#include "modules/disk.h"

using namespace std;

Disk::Disk(){
	//TODO: Constructor
	size = new int;
	*size = 0;
	capacity = new int;
	*capacity = 2048;
	*disk = new string[*capacity];
}

void Disk::add(string *entry){
	if (!isFull()){
		disk[*size]=entry;
		size++;
	}
}

string* Disk::get(int *index){
	return disk[*index];
}

bool Disk::isFull(){
	if (size >= capacity){
		return true;
	}else{
		return false;
	}
}
int* Disk::getSize(){
	return size;
}