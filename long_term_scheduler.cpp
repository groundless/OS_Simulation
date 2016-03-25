//============================================================================
// Name        : long_term_scheduler.cpp
// Author      :
// Version     :
// Description : Source file for long term scheduler
//============================================================================

#include "long_term_scheduler.h"

/*
 * main_memory array contains sixteen indexes, each representing
 * one megabyte of memory. Each index will contain the process_id
 * of the process occupying that megabyte of memory.
 */
#define MEM_SIZE 16
int main_memory[MEM_SIZE];
int available_memory;

/*
 * Primary vectors of PCBs for the NEW and READY queue.
 */
std::vector<PCB> new_queue;
std::vector<PCB> ready_queue;

/*
 * Blocked queue for processes waiting on IO
 */
std::vector<PCB> blocked_queue;

/*
 * List of processes that have completed. May not be needed.
 * But used anyway to store the history of processes in the OS.
 */
std::vector<PCB> finished_list;

/*
 * The main running process.
 * Possibly a better way to implement this.
 */
PCB running_process;


/*
 * Basic initializations go here to keep the code clean.
 */
void initialize_memory()
{
	available_memory = MEM_SIZE;
	running_process.set_state("NULL");
}

/*
 * Simulates the arrival of a new process into the OS.
 */
void new_process_arrival(PCB new_arrival)
{
	if (new_arrival.check_state("NULL"))
		return;

	new_arrival.set_state("NEW");
	new_queue.push_back(new_arrival);
	allocate_memory();
}

/*
 * Basically the long term scheduler, maybe could use a different name:
 * Uses the LIFO property of the queue to simulate process arrival i.e. FCFS.
 */
void allocate_memory()
{
	if (new_queue.empty()){
		if (DEBUG) cout << "DEBUG: (allocate_memory): New queue is empty." << endl;
		return;
	}

	PCB next_process = new_queue.back();

	if (next_process.get_size() <= available_memory){
		if (DEBUG) cout << "DEBUG: (allocate_memory): available_memory " << available_memory << endl;
		if (DEBUG) cout << "DEBUG: (allocate_memory): Process " << next_process.get_id() << " is size " << next_process.get_size() << endl;
		available_memory -= next_process.get_size();
		new_queue.pop_back();
		next_process.set_state("READY");
		ready_queue.push_back(next_process);
	}
}

/*
 * Increments elapsed time of the current RUNNING process.
 */
void execute_running_process () {
	if (running_process.check_state("NULL")) {
		if (DEBUG) cout << "DEBUG: (execute_running_process): No currently running process" << endl;
		return;
	}
	running_process.execute_instruction();
	if (DEBUG) cout << "DEBUG: (execute_running_process): Running Process remaining time to complete: " << running_process.runtime_remaining() << endl;

	if (running_process.runtime_remaining() == 0) {
		if (DEBUG) cout << "DEBUG: (execute_running_process): Process has finished running" << endl;
		process_exit();
	}
}

/*
 * Running -> Exit
 * Remove process from main memory, place in some kind of finished queue?
 * Finished queue for tracking or debugging purposes?
 */

void process_exit() {
	int i;
	for (i = 0; i < MEM_SIZE; i++) {
		if (main_memory[i] == running_process.get_id())
			main_memory[i] = 0;
	}

	// Finish fixing the main_memory array
	available_memory += running_process.get_size();
	running_process.set_state("EXIT");
	PCB finished_process = running_process;
	finished_list.push_back(finished_process);
	running_process.set_state("NULL");
}

/*
 * Check for interrupts, including both IO requests as well as
 * interrupts from the short term scheduling because of time slicing.
 */
void check_interrupts () {

	// Check if the running process has any IO requests
	if (running_process.request_io()) {
		if (DEBUG) cout << "DEBUG: (check_interupts): Running Process has an IO Request " << endl;
		// Process IO requests
		running_process.finish_iorequest();
	}

}

/*
 * Basically FCFS temporarily, also not fully working.
 * This should make use of debug statements, since getting a good implementation
 * working that we also know is working will take some time.
 */
void short_term_scheduler () {
	if (running_process.check_state("NULL")) {
		if (DEBUG) cout << "DEBUG: (short_term_scheduler): no process currently running" << endl;
		if (ready_queue.empty()) {
			if (DEBUG) cout << "DEBUG: (short_term_scheduler): Ready Queue is currently empty" << endl;
			return;
		}
		running_process = ready_queue.back();
		ready_queue.pop_back();
		if (DEBUG) cout << "DEBUG: (short_term_scheduler): put process: " << running_process.get_id() << " into running" << endl;
	}
	else {
		if (DEBUG) cout << "DEBUG: (short_term_scheduler): Current running process ID is :" << running_process.get_id() << endl;
		if (running_process.runtime_remaining() == 0) {
			if (DEBUG) cout << "DEBUG: (short_term_scheduler): Running Process has finished " << endl;
			process_exit();
		}
	}
}


/*
 * Debugging function, prints out the processes in the NEW and READY queue.
 */
void debug_print_new_ready () {
	unsigned int index;
	if (DEBUG) {
		cout << "DEBUG: New Queue" << endl;
		cout << "DEBUG: New Queue size is " << new_queue.size() << endl;
		for (index = 0; index < new_queue.size(); index++) {
			cout << "DEBUG: New Queue - Process " << new_queue.at(index).get_id() << " size is: " << new_queue.at(index).get_size() << endl;
		}
		cout << "DEBUG: Ready Queue" << endl;
		cout << "DEBUG: Ready Queue size is " << ready_queue.size() << endl;
		for (index = 0; index < ready_queue.size(); index++) {
			cout << "DEBUG: Ready Queue -  Process " << ready_queue.at(index).get_id() << " size is: " << ready_queue.at(index).get_size() << endl;
		}
		if (!running_process.check_state("NULL")) {
			cout << "DEBUG: Running Process - " << running_process.get_id() << " size is " << running_process.get_size() << endl;
		}
	}
}
