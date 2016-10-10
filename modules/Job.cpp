#include <iostream>
#include <string>
#include <vector>

#include "Job.h"

using namespace std;

Job::Job() {
	number = 0;
	instructions = new vector<string>();
	data = new vector<string>();
}

Job::Job(int num) {
	number = num;
	instructions = new vector<string>();
	data = new vector<string>();
}

void Job::addInstruction(string line) {
	instructions->push_back(line);
}

void Job::addData(string line) {
	data->push_back(line);
}