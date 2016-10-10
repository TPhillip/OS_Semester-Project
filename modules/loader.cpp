#include <fstream>
#include <string>
#include <algorithm>
#include<sstream>

#include "loader.h"
#include "Job.h"

using namespace std;

Loader::Loader(){
	fileName = "";
}

string Loader::getBinaryStringFromHexString(string sHex)
{
	transform(sHex.begin(), sHex.end(), sHex.begin(), ::tolower);
	string sReturn = "";
	for (int i = 0; i < sHex.length(); ++i)
	{
		switch (sHex[i])
		{
		case '0': sReturn.append("0000"); break;
		case '1': sReturn.append("0001"); break;
		case '2': sReturn.append("0010"); break;
		case '3': sReturn.append("0011"); break;
		case '4': sReturn.append("0100"); break;
		case '5': sReturn.append("0101"); break;
		case '6': sReturn.append("0110"); break;
		case '7': sReturn.append("0111"); break;
		case '8': sReturn.append("1000"); break;
		case '9': sReturn.append("1001"); break;
		case 'a': sReturn.append("1010"); break;
		case 'b': sReturn.append("1011"); break;
		case 'c': sReturn.append("1100"); break;
		case 'd': sReturn.append("1101"); break;
		case 'e': sReturn.append("1110"); break;
		case 'f': sReturn.append("1111"); break;
		}
	}
	return sReturn;
}

void Loader::readFile(string fname){
	fileName = fname;
	string line;
	ifstream myfile(fileName);
	if (myfile.is_open())	{
		string fieldType = "";
		int jobNumber = 0;
		Job *newJob;
		while (getline(myfile, line)){
			if (line.substr(0, 2) == "//") {
				stringstream parser(line.substr(3));
				//determine whether next instruction set are data or job (or end)
				if (parser.good()) { 
					parser >> fieldType;
					transform(fieldType.begin(), fieldType.end(), fieldType.begin(), ::tolower);
				}
				//Get the job number
				if (parser.good() && fieldType=="job") { 
					string temp;
					parser >> temp;
					stringstream hexNum;
					hexNum << hex << temp;
					hexNum >> jobNumber;
				}
				//create new job with job number
				if (fieldType == "job") {
					newJob = new Job(jobNumber);
				}
				if (fieldType == "end") {
				//Save newJob to memory here...
				}
			}
			else if (line == "")
				continue;
			else{
				if (fieldType == "job") {
					newJob->addInstruction(getBinaryStringFromHexString(line.substr(2)));
				}
				else if (fieldType == "data") {
					newJob->addData(getBinaryStringFromHexString(line.substr(2)));
				}
			}
		}
		myfile.close();
	}
	else return;

}

