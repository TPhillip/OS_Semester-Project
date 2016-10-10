#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Loader{
private:
	string fileName;
	string getBinaryStringFromHexString(string sHex);
public:
	Loader();
	void readFile(string fname);
};