#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Loader{
private:
	string fileName;
	vector<string> *instructionVector;
public:
	Loader();
	void readFile(string fname);
	vector<string> *getInstructionVector();
};