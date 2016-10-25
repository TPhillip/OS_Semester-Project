#include "modules/disk.h"

using namespace std;

Disk::Disk(){
	//TODO: Constructor
	size =0;
}

void Disk::add(string entry){
	if (!isFull()){
		disk[size]=entry;
		size+=1;
	}
}

string Disk::get(int index){
	return disk[index];
}

bool Disk::isFull(){
	if (size >= capacity){
		return true;
	}else{
		return false;
	}
}
int Disk::getSize(){
	return size;
}