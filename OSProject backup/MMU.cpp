#include "MMU.h"


bool MMU::ram_address_available(int addr, PCB *pcb) {
	bool found = false;
	int i = 0;
	for (vector<Frame>::iterator it = frameTableVector->begin(); it != frameTableVector->end(); ++it) {
		if (!it->valid) {
			found = true;
		}
		++i;
	}
	return found;
}

bool MMU::disk_address_available(int addr) {
	bool found = false;
	if (pageTableVector->size() == maxNumPages) {
		for (vector<Page>::iterator it = pageTableVector->begin(); it != pageTableVector->end(); ++it) {
			if (!it->valid) {
				found = true;
				break;
				/*
				for each (int pageEntry in it->addressAray)
				{
					if (addr == pageEntry)
						return false;
				}
				*/
			}
		}
	}
	else {
		found = true;
	}
	return found;
}


int MMU::find_empty_frame() {
	int address = -1;
	int i = 0;
	for (vector<Frame>::iterator it = frameTableVector->begin(); it != frameTableVector->end(); ++it) {
		if (it->address == -1) {
			return i;
		}
		++i;
	}
	return address;
}

int MMU::find_empty_page() {
	int address = -1;
	int i = 0;
	for (vector<Page>::iterator it = pageTableVector->begin(); it != pageTableVector->end(); ++it) {
		if (it->address == -1) {
			return i;
			break;
		}
		++i;
	}
	
	return address;
}


void MMU::createPage(int instruction_number) {
		Page *newPage = new Page();
		newPage->address = -1;
		newPage->valid = false;
		pageTableVector->push_back(*newPage);
}
void MMU::createFrame(int instruction_number) {
		Frame *newFrame = new Frame();
		newFrame->address = -1;
		newFrame->valid = false;
		frameTableVector->push_back(*newFrame);
}

void MMU::clearPage(int pageNum) {
	Page* referencePage = &pageTableVector->at(pageNum);
	for (int i = 0; i < 3; ++i){
		int address = pageNum * 4;
		seagate2048->set(pageNum + i, "");
	}
	referencePage->address = -1;
}
void MMU::clearFrames(PCB *pcb) {

	for (int i = 0; i < pcb->get_page_count(); ++i) {
		int frame = pcb->get_frame(i);
		if (frame != -1) {
			(&frameTableVector->at(frame))->valid = false;
			(&frameTableVector->at(frame))->address = -1;
		}
	}
}

void MMU::write_to_disk(int pageNum, int offset, string toWrite) {
	Page* referencePage = &pageTableVector->at(pageNum);
	int index = (pageNum * 4) + offset;
	seagate2048->set(index, toWrite);
	referencePage->valid = false;
	referencePage->address=-2;
}

void MMU::write_to_ram(int pcbPageNum, int offset, string entry, PCB *pcb) {
	int frameNum = pcb->get_frame(pcbPageNum);
	evga1024->set(((frameNum * 4) + offset), entry);
	int diskPage = pcb->get_disk_page(pcbPageNum);
	write_to_disk(diskPage, offset, entry);
}
string MMU::read_from_ram(int frameNum, int offset) {
	Frame* referenceFrame = &frameTableVector->at(frameNum);
	return evga1024->get_from_RAM(frameNum*4 + offset);
}
string MMU::read_from_disk(int pageNum, int offset) {
	Page* referencePage = &pageTableVector->at(pageNum);
	int referenceAddress = referencePage->address;
	return seagate2048->get_from_Disk(((pageNum * 4) + offset));
}
bool MMU::is_page_in_ram(int pageNum) {
	Frame* referenceFrame = &frameTableVector->at(pageNum);
	return referenceFrame->valid;
}
void MMU::service_page_fault(PCB *pcb) {
	int free_frame = find_empty_frame();
	int req_page = pcb->get_req_page();
	if (free_frame >= 0) {
		int diskPage = req_page + pcb->get_instruct_page();
		stat->incRamUsage(pcb->get_process_ID());
		Page* referencePage = &pageTableVector->at(diskPage);
		Frame* referenceFrame = &frameTableVector->at(free_frame);		
		pcb->set_new_frame(free_frame, req_page);
		pcb->set_page_valid(true, req_page);
		for (int i = 0; i < 4; ++i) {
			string entry = read_from_disk(diskPage, i);
			write_to_ram(req_page, i, entry, pcb);
		}
		referencePage->address = free_frame;
		referenceFrame->address = diskPage;
		referenceFrame->valid = true;
		referencePage->valid = true;
		pcb->set_page_valid(true, req_page);	
		pcb->set_is_running(false);
		pcb->set_faulty(false);
	}
}
