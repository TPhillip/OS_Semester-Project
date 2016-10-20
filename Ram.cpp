#include "Ram.h"

Ram::Ram()
{
	size = 0;
}

Ram::~Ram()
{
}
void Ram::add(string entry){
	if (!isFull()){
		ram[size]=entry;
		size+=1;
	}
}
bool Ram::isFull(){
	if (size >= capacity){
		return true;
	}else{
		return false;
	}
}

