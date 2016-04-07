//============================================================================
// Name		   : long_term_scheduler.cpp
// Author	   :
// Version	   :
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
 * Counts the number of cycles for an IO Request
 * Possibly a cleaner way to implement this
 */
int io_cycle_count = 0;

/*
 * Basic initializations go here to keep the code clean.
 */
void initialize_memory()
{
	available_memory = MEM_SIZE;
	running_process.set_state("NULL");

	for(int i = 0; i < MEM_SIZE; i++)
		main_memory[i] = 0;
}

//
// New processes are allocated memory in the main_memory array. 
//
void memory_allocate(PCB new_arrival)
{
	int PID = new_arrival.get_id();
	int requested_memory = new_arrival.get_size();
	int free_memory = 0;

	while(main_memory[free_memory] != 0)
		free_memory++;

	if((MEM_SIZE - free_memory) >= requested_memory)
		for(int i = free_memory; i < free_memory + requested_memory; i++)
			main_memory[i] = PID;
	else
	{
		if (DEBUG) cout << "(memory_allocate): ERROR Not enough memory for process " << PID << endl;
	}
}

// 
// Processes that are finished running have their memory removed. 
// Remaining memory is then shifted down. 
//
void memory_deallocate(PCB finished_process)
{
	int i = 0;
	int j;
	int PID = finished_process.get_id();
	while(main_memory[i] != PID)
		i++;
	j = i;
	while(main_memory[j] == PID)
	{
		main_memory[j] = 0;
		j++;
	}
	while(main_memory[j] != 0 && j < MEM_SIZE)
	{
		main_memory[i] = main_memory[j];
		main_memory[j] = 0;
		i++;
		j++;
	}
}

//
// Print out the main_memory array visually. 
// For debugging purposes. 
//
void print_memory()
{
	if (DEBUG)
	{
		for (int i = 0; i < MEM_SIZE; i++)
		{
			cout << "Main Memory " << i << ": PID " << main_memory[i] << endl;
		}
	}
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
}

/*
 * Uses FCFS to simulate process arrival.
 */
void long_term_scheduler()
{
	// If there is nothing is the NEW queue, then no decisions are to be made.
	if (new_queue.empty()){
		if (DEBUG) cout << "DEBUG: (allocate_memory): New queue is empty." << endl;
		return;
	}

	PCB next_process = new_queue.front();

	// Check if memory is available yet for the next process in line.
	if (next_process.get_size() <= available_memory) {

		if (DEBUG) cout << "DEBUG: (allocate_memory): available_memory " << available_memory << endl;
		if (DEBUG) cout << "DEBUG: (allocate_memory): allocating Process " << next_process.get_id() << " with size " << next_process.get_size() << endl;

		available_memory -= next_process.get_size();

		if (DEBUG) cout << "DEBUG: (allocate_memory): allocated memory, available_memory now " << available_memory << endl;

		memory_allocate(next_process);

		new_queue.erase(new_queue.begin());
		next_process.set_state("READY");
		ready_queue.push_back(next_process);
	}
	print_memory();
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

	// Deallocate memory from the process
	memory_deallocate(running_process);
	available_memory += running_process.get_size();

	// Main running process is now READY->EXIT
	running_process.set_state("EXIT");

	// Store our finished process onto finished_list
	// May not be necessary, but useful for debugging later
	PCB finished_process = running_process;
	finished_list.push_back(finished_process);

	// Running process is now NULL
	PCB null_process;
	running_process = null_process;
	running_process.set_state("NULL");
}

/*
 * Check for interrupts, including both IO requests as well as
 * interrupts from the short term scheduler because of time slicing.
 * An I/O operation takes somewhere between 25 to 50 cycles.
 * A time slice occurs every ten cycles.
 */
void check_interrupts () {

	// Check if the running process has any IO requests
	if (running_process.request_io()) {

		// Set the counter for how many cycles until IO Completion
		// Should be a random number between 25 - 50
		if (blocked_queue.empty()) io_cycle_count = 25;

		if (DEBUG) cout << "DEBUG: (check_interupts): Running Process has an IO Request " << endl;

		// Indicate that the running process is now BLOCKED
		// Blocked processes remain in main memory
		running_process.set_state("BLOCKED");

		// Block running process while IO request is fulfilled
		blocked_queue.push_back(running_process);

		// Currently no running process, set a null process,
		// in order to prevent any erroneous checks from passing
		// maybe the running_process should just be a vector?
		PCB null_process;
		running_process = null_process;
		running_process.set_state("NULL");
	}
	// Check if the IO device is in use
	if (io_cycle_count > 0) {

		// Execute a cycle of the IO device
		io_cycle_count--;
		if (DEBUG) cout << "DEBUG: (check_interupts): io_cycle_count is " << io_cycle_count << endl;

		// Check if the IO has completed
		if (io_cycle_count == 0) {
			if (DEBUG) cout << "DEBUG: (check_interupts): IO Request Completed " << endl;
			if (DEBUG) cout << "DEBUG: (check_interupts): Process " << blocked_queue.front().get_id() << " has completed an IO Request " << endl;

			// Simulate completion of the IO request
			blocked_queue.front().finish_iorequest();

			// Move the process back onto the end of the Ready Queue
			ready_queue.push_back(blocked_queue.front());

			// Remove the process from the blocked queue
			blocked_queue.erase(blocked_queue.begin());

			// Check if there are still outstanding IO Requests
			if (!blocked_queue.empty()) {

				// Reset the cycle count to somewhere between 25 - 50 cycles
				 io_cycle_count = 25;
				 if (DEBUG) cout << "DEBUG: (check_interupts): Resetting io_cycle_count to " << io_cycle_count << endl;
			}
		}
	}
}


/*
 * Debugging function, prints out the processes in the NEW and READY queue.
 */
void debug_print_new_ready () {
	unsigned int index;
	if (DEBUG) {
		cout << "DEBUG: New Queue size is " << new_queue.size() << endl;
		for (index = 0; index < new_queue.size(); index++) {
			cout << "DEBUG: New Queue - Process " << new_queue.at(index).get_id() << " size is: " << new_queue.at(index).get_size() << endl;
		}
		cout << "DEBUG: Ready Queue size is " << ready_queue.size() << endl;
		for (index = 0; index < ready_queue.size(); index++) {
			cout << "DEBUG: Ready Queue -  Process " << ready_queue.at(index).get_id() << " size is: " << ready_queue.at(index).get_size() << endl;
		}
		cout << "DEBUG: Blocked Queue size is " << blocked_queue.size() << endl;
		for (index = 0; index < blocked_queue.size(); index++) {
			cout << "DEBUG: Blocked Queue -  Process " << blocked_queue.at(index).get_id() << " size is: " << blocked_queue.at(index).get_size() << endl;
		}
		if (!running_process.check_state("NULL")) {
			cout << "DEBUG: Running Process - " << running_process.get_id() << " size is " << running_process.get_size() << endl;
		}
	}
}
