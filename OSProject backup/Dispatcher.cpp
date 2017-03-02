// Zane W. Gabriel K. Alex C. Tevin P.
#include "Dispatcher.h"

//this method loops through the PCBs, checking to see if they are not running, are in ram, and hasn't been completed, it sends it to the CPU
void Dispatcher::dispatch(CPU *Intel)
{
	for(PCB *cursor = PCB2; cursor != NULL; cursor = cursor->get_link())
	{
		if(!cursor->get_is_running() && !cursor->get_completed() && !cursor->is_faulty())
		{
			cursor->set_is_running(true);
			Intel->set_to_run(cursor->get_first_instruct_ram()  +  cursor->get_program_counter(), cursor);
			break;
		}
	}
	service_faults();
}
void Dispatcher::service_faults() {
	for (PCB *cursor = PCB2; cursor != NULL; cursor = cursor->get_link())
	{
		if (cursor->is_faulty())
		{
			mmu->service_page_fault(cursor);
			return;
		}
	}
}