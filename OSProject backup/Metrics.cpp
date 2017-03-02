#include "Metrics.h"

void Metrics::logStart(int pid) {
	processStatistics *procStat = new processStatistics();
	procStat->jobStart = clock();
	procStat->runningTime = 0;
	metricMap->insert(std::make_pair(pid, procStat));
}

void Metrics::logCompletion(int pid) {
	metricMap->at(pid)->jobFinish = clock();
	metricMap->at(pid)->completionTime = double(metricMap->at(pid)->jobFinish - metricMap->at(pid)->jobStart) / CLOCKS_PER_SEC;
}

void Metrics::logRamUsage(int pid, int frames) {
	metricMap->at(pid)->ramFramesOccupied = frames;
}

clock_t Metrics::procPunchIn() {
	return clock();
}

void Metrics::procPunchOut(int pid, clock_t comparison) {
	metricMap->at(pid)->runningTime += double(clock() - comparison) / CLOCKS_PER_SEC;
}

void Metrics::logIoRD(int pid) {
	metricMap->at(pid)->ioRD++;
}

void Metrics::logIoWR(int pid) {
	metricMap->at(pid)->ioWR++;
}

void Metrics::incRamUsage(int pid) {
	metricMap->at(pid)->ramUsage++;
}

void Metrics::incCpuCycles(int pid) {
	metricMap->at(pid)->cpuCycles++;
}

void Metrics::incPageFaults(int pid) {
	metricMap->at(pid)->pageFaults++;
}

void Metrics::logProgramEnd() {
	endTime = clock();
}

std::string Metrics::toString() {
	std::stringstream _out;
	outfile << "Pid\t\tCompletion\t\tRam %\t\tWatit Time\tI/O RD\tI/O WR\tCPU Cyc.\tPage Faults\n*******************************************************************************************************************" << std::endl;
	int i = 0;
	double wait_sum = 0;
	double completion_sum = 0;
	double totalRam = 0;
	for (std::map<int, processStatistics*>::iterator it = metricMap->begin(); it != metricMap->end(); it++)
	{
		double osTime = endTime - initialTime;
		outfile << it._Ptr->_Myval.first;
		outfile << "\t\t" << it._Ptr->_Myval.second->completionTime << "s";
		outfile << "\t\t\t" << ((float)it._Ptr->_Myval.second->ramUsage / 1024) * 100 << "%";
		outfile << "\t" << it._Ptr->_Myval.second->completionTime - it._Ptr->_Myval.second->runningTime << "s";
		outfile << "\t\t" << it._Ptr->_Myval.second->ioRD;
		outfile << "\t\t" << it._Ptr->_Myval.second->ioWR;
		outfile << "\t\t" << it._Ptr->_Myval.second->cpuCycles;
		outfile << "\t\t\t" << it._Ptr->_Myval.second->pageFaults << std::endl;

		completion_sum += it._Ptr->_Myval.second->completionTime;
		totalRam += it._Ptr->_Myval.second->ramUsage;
		wait_sum += (it._Ptr->_Myval.second->completionTime - it._Ptr->_Myval.second->runningTime);
		i++;
	}
	outfile << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
	outfile << "Average completion time\t" << (completion_sum / i) << "s" << std::endl;
	outfile << "Average wait time\t" << (wait_sum / i) << "s" << std::endl;
	outfile << "Average RAM Usage\t" << ((totalRam / i) / 1024) * 100 << "%" << std::endl;
	return _out.str();
}