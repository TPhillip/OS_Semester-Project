#include <iostream>
#include <string>

#include "loader.h"

using namespace std;

Loader::Loader(){
	
}

void Loader::readFile(string fname){
	filename = fname;
	cout << filename << endl;
}