#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Job {
private:
	vector<string> *instructions;
	vector<string> *data;
	int number;
public:
	Job();
	Job(int num);
	void addInstruction(string line);
	void addData(string line);
};