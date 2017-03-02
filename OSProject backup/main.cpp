// Zane W. Gabriel K. Tevin P.
// 27 Oct 2016 7:45pm

#include <stdio.h>
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Disk.h"
#include "PCB.h"
#include "Loader.h"
#include "RAM.h"
#include "Scheduler.h"
#include "Dispatcher.h"
#include "CPU.h"
#include "Metrics.h"
#include "MMU.h"

#include <cassert>
using namespace std;

bool check_for_completion(PCB *PCB2);

int main(int argc, char **argv)
{
	string scheduleOutputFileName = "Simulation_scheduling.txt";
	if (std::ofstream(scheduleOutputFileName)) {
		remove(scheduleOutputFileName.c_str());
	}

	for (int setCores = 1; setCores < 5; setCores += 3) {
		std::ofstream scheduleOutfile;
		scheduleOutfile.open(scheduleOutputFileName, std::ios_base::app);
		cout << "\nSimulating " << setCores << " core system" << endl;
		cout << "********************************************************\n" << endl;
		scheduleOutfile << "\nSimulating " << setCores << " core system" << endl;
		scheduleOutfile << " Simulating " << setCores << " core system" << endl;
		scheduleOutfile.close();
		for (int sort = 0; sort < 3; ++sort) {
			

			//set 0 for FCFS, 1 for priority, 2 for SJF
			int sortingAlgorithm = sort;
			assert(sortingAlgorithm >= 0);
			assert(sortingAlgorithm <= 2);
			//Number of cpus to simulate.
			const int cores = setCores;

			string coreDumpOutputFileName = "";
			string diskDumpOutputFileName = "";
			string metricsOutputFileName = "";

			string complete = "";
			if (sortingAlgorithm == 0) {
				coreDumpOutputFileName = "Core_dump_FIFO_" + to_string(cores) + "_core_run.txt";
				diskDumpOutputFileName = "Disk_dump_FIFO_" + to_string(cores) + "_core_run.txt";
				metricsOutputFileName = "Metrics_FIFO_" + to_string(cores) + "_core_run.txt";
				complete = "Simulatiion of FIFO " + to_string(cores) + " core run completed successfully";
				//scheduleOutputFileName = "Schedule_FIFO_" + to_string(cores) + "_core_run.txt
				cout << "sorting Algorithm is FIFO" << endl;
			}
			else if (sortingAlgorithm == 1) {
				coreDumpOutputFileName = "Core_dump_Priority_" + to_string(cores) + "_core_run.txt";
				diskDumpOutputFileName = "Disk_dump_Priority_" + to_string(cores) + "_core_run.txt";
				metricsOutputFileName = "Metrics_Priority_" + to_string(cores) + "_core_run.txt";
				complete = "Simulatiion of Priority sorted " + to_string(cores) + " core run completed successfully";
				//scheduleOutputFileName = "Schedule_Priority_" + to_string(cores) + "_core_run.txt";
				cout << "sorting Algorithm is Priority" << endl;
			}
			else {
				coreDumpOutputFileName = "Core_dump_SJF_" + to_string(cores) + "_core_run.txt";
				diskDumpOutputFileName = "Disk_dump_SJF_" + to_string(cores) + "_core_run.txt";
				metricsOutputFileName = "Metrics_SJF_" + to_string(cores) + "_core_run.txt";
				complete = "Simulatiion of SJF sorted " + to_string(cores) + " core run completed successfully";
				//scheduleOutputFileName = "Schedule_SJF_" + to_string(cores) + "_core_run.txt";
				cout << "sorting Algorithm is SJF" << endl;
			}

			Metrics *stat = new Metrics(metricsOutputFileName);

			string file = "Program-File.txt";
			Disk *drive = new Disk;
			RAM *corsair1024 = new RAM;
			PCB *pcb = new PCB;
			MMU *mmu = new MMU(drive, corsair1024, stat);
		
			cout << endl;
			Loader *loading = new Loader(drive, pcb, file, sortingAlgorithm, mmu, scheduleOutputFileName);
			loading->read_File();
			pcb = loading->get_headPtr();			//point to new head pointer from loader
			
			Scheduler *Schedule = new Scheduler(drive, pcb, corsair1024, stat, mmu, coreDumpOutputFileName);
			Dispatcher *Dispatch = new Dispatcher(pcb, mmu);
			vector<CPU*> *intels = new vector<CPU*>;
			for (int i = 0; i < cores; ++i) {
				CPU *temp = new CPU(corsair1024, pcb, stat, mmu);
				intels->push_back(temp);
			}
			bool run_time = true;
			Schedule->load_processes();
			while (run_time)
			{
				run_time = check_for_completion(pcb);
				Schedule->run_scheduler();
				for (int i = 0; i < cores; ++i) {
					CPU *intel = intels->at(i);
					Dispatch->dispatch(intel);
				}
				for (int i = 0; i < cores; i += 1) {
					CPU *intel = intels->at(i);
					while (!intel->isDone() && !intel->get_page_fault()) {
						intel->decode_and_execute();
					}
				}
			}

			if (std::ofstream(diskDumpOutputFileName)) {
				remove(diskDumpOutputFileName.c_str());
			}
			std::ofstream outfile;
			outfile.open(diskDumpOutputFileName, std::ios_base::out);
			for (int k = 0; k < 16; ++k) {
				for (int i = k*128; i < 32 +(128*k); ++i) {
					for (int j = i; j < 128 + (128 * k); j += 32) {
						string entry = drive->get_from_Disk(j);
						string num = to_string(j);
						if (entry.length() == 0) {
							entry = "\t";
						}
						for (int m = 0; m < 8 - entry.length(); ++m) {
							entry += " ";
						}
						for (int m = 0; m < 8 - num.length(); ++m) {
							num += "  ";
						}
						outfile << entry << "  " << num<< "\t\t";
					}
					outfile << endl;
				}
			}
			outfile.close();
			
			stat->logProgramEnd();
			cout << stat->toString();
			/*
			delete loading;
			delete drive;
			delete corsair1024;
			delete mmu;
			delete Schedule;
			delete Dispatch;
			for (int i = 0; i < cores; ++i) {
				delete intels->at(i);
			}
			delete intels;
			*/
			cout << complete << endl;
			cout << "------------------------------------------------------------\n" << endl;
		}
		cout << "********************************************************" << endl;
		cout << "Simulation of " << setCores << "core run completed successfully" << endl;
		cout << "********************************************************\n" << endl;
	}
	string hello;
	cin >> hello;
	return 0;
}



bool check_for_completion(PCB *PCB2)
{
	for(PCB *cursor = PCB2; cursor != NULL; cursor = cursor->get_link())
	{
		if(!cursor->get_completed())
		{
			return true;
		}
	}
	return false;
}