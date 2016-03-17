//============================================================================
// Name        : long_term_scheduler.h
// Author      :
// Version     : 0.01
// Description : Long term scheduling bringing processes into NEW and NEW->READY
//============================================================================

#include <vector>
#include "pcb.h"
#include "input_processing.h"

#ifndef LONG_TERM_SCHEDULER_H_
#define LONG_TERM_SCHEDULER_H_

/*
 * Description of memory implementation goes here:
 * I'll ask the Professor about how complicated this could be.
 * I.e. Do we use an array or just simply an integer?
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
 * The main running process.
 * Possibly a better way to implement this.
 */
PCB running_process;

/*
 * Some of these functions should go into another .cpp file
 * Right now this header file lumps together long_term and short_term
 * scheduling functions, which is bad form, and also in general
 * having function definitions in a header file is bad practice haha.
 */
void initialize_memory();
void new_process_arrival();
void allocate_memory();

void execute_running_process();
void short_term_scheduler();


/*
 * Debugging functions.
 * Just how many of these will appear is yet to be seen.
 */
void debug_print_new_ready();



/*
 * Basic initializations go here to keep the code clean.
 */
void initialize_memory()
{
	available_memory = MEM_SIZE;
	running_process.state = "NULL";
}

/*
 * Simulates the arrival of a new process into the OS.
 */
void new_process_arrival(PCB new_arrival)
{
	if (new_arrival.state == "NULL")
		return;

	new_arrival.state = "NEW";
	new_queue.push_back(new_arrival);
	allocate_memory();
}

/*
 * Basically the long term scheduler, maybe could use a different name:
 * Uses the LIFO property of the queue to simulate process arrival -
 */
void allocate_memory()
{
	if (new_queue.empty())
		return;

	PCB next_process = new_queue.back();

	if (next_process.size <= available_memory){

		available_memory -= next_process.size;
		new_queue.pop_back();
		next_process.state = "READY";
		ready_queue.push_back(next_process);
	}
}

/*
 * Increments elapsed time of the current RUNNING process.
 */
void execute_running_process () {
	if (running_process.state == "NULL") {
		if (DEBUG) cout << "DEBUG: No currently running process" << endl;
		return;
	}
	running_process.elapsed_runtime++;
	if (DEBUG) cout << "DEBUG: Running Process current runtime is: " << running_process.elapsed_runtime << endl;
}

/*
 * Basically FCFS temporarily, also not fully working.
 * This should make use of debug statements, since getting a good implementation
 * working that we also know is working will take some time.
 */
void short_term_scheduler () {
	if (running_process.state == "NULL") {
		if (DEBUG) cout << "DEBUG: Short term scheduler sees no process currently running" << endl;
		if (ready_queue.empty()) {
			if (DEBUG) cout << "DEBUG: Short term scheduler sees Ready Queue is currently empty" << endl;
			return;
		}
		running_process = ready_queue.back();
		ready_queue.pop_back();
		if (DEBUG) cout << "DEBUG: Short term scheduler put Process: " << running_process.process_id << " into running" << endl;
	}
	else
		if (DEBUG) cout << "DEBUG: Short term scheduler: Current running process ID is :" << running_process.process_id << endl;
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
			cout << "DEBUG: New Queue - Process " << (index + 1) << " size is: " << new_queue.at(index).size << endl;
		}
		cout << "DEBUG: Ready Queue" << endl;
		cout << "DEBUG: Ready Queue size is " << ready_queue.size() << endl;
		for (index = 0; index < ready_queue.size(); index++) {
			cout << "DEBUG: Ready Queue - Process " << (index + 1) << " size is: " << ready_queue.at(index).size << endl;
		}
	}
}


#endif /* LONG_TERM_SCHEDULER_H_ */
