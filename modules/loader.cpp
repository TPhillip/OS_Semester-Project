#include <fstream>
#include <string>

#include "loader.h"

using namespace std;

Loader::Loader(){
	fileName = "";
	instructionVector = new vector<string>;
}

void Loader::readFile(string fname){
	fileName = fname;
	string line;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.substr(0, 2) == "//" || line == "")
				continue;
			else{
				instructionVector->push_back(line.substr(3));
			}
		}
		myfile.close();
	}
	else return;
}

vector<string> *Loader::getInstructionVector(){
	return instructionVector;
}