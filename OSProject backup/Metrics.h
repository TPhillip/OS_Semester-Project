#pragma once
#include <ctime>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

class Metrics
{
private:
	std::clock_t initialTime;
	std::clock_t endTime;
	std::ofstream outfile;
	struct processStatistics {
		clock_t jobStart;
		clock_t jobFinish;
		double completionTime;
		double runningTime;
		int ioRD;
		int ioWR;
		int ramFramesOccupied;
		int cacheFramesOccupied;
		int ramUsage;
		int cpuCycles;
		int pageFaults;

	};
	std::map<int, processStatistics*> *metricMap;
public:
	Metrics(std::string metricsOutputFileName) {
		initialTime = clock();
		metricMap = new std::map<int, processStatistics*>();
		if (std::ofstream(metricsOutputFileName)) {
			remove(metricsOutputFileName.c_str());
		}

		outfile.open(metricsOutputFileName, std::ios_base::out);
	};
	~Metrics();
	void logStart(int pid);
	void logCompletion(int pid);
	void logIoTask(int pid);
	void logRamUsage(int pid, int frames);
	clock_t procPunchIn();
	void procPunchOut(int pid, clock_t comparison);
	void logIoRD(int pid);
	void logIoWR(int pid);
	void incRamUsage(int pid);
	void incCpuCycles(int pid);
	void incPageFaults(int pid);
	void logProgramEnd();
	std::string toString();
};