//============================================================================
// Name		   : long_term_scheduler.cpp
// Author	   :
// Version	   :
// Description : Source file for long term scheduler
//============================================================================

#include "long_term_scheduler.h"

int available_memory;

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

	// Memory has been allocated, update UI.
	state_changed_flag = true;
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

	// Memory has been deallocated, update UI.
	state_changed_flag = true;
}


/*
 * Simulates the arrival of a new process into the OS.
 */
void new_process_arrival(PCB new_arrival)
{
	if (new_arrival.check_state("NULL"))
		return;

    state_changed_string = "State changed for process " + new_arrival.get_string_id() + " changed from state " + new_arrival.get_state() + " to the NEW state";

	new_arrival.set_state("NEW");
	new_queue.push_back(new_arrival);

	// A new process enters the system, the display should now update.
	state_changed_flag = true;
}

/*
 * Uses FCFS to simulate process arrival.
 */
void long_term_scheduler()
{
	// If there is nothing is the NEW queue, then no decisions are to be made.
	if (new_queue.empty()){
		if (DEBUG) cout << "DEBUG: (long_term_scheduler): New queue is empty." << endl;
		return;
	}

	PCB next_process = new_queue.front();

	// Check if memory is available for the next process in line.
	if (next_process.get_size() <= available_memory) {

		if (DEBUG) cout << "DEBUG: (long_term_scheduler): available_memory " << available_memory << endl;
		if (DEBUG) cout << "DEBUG: (long_term_scheduler): allocating Process " << next_process.get_id() << " with size " << next_process.get_size() << endl;

		available_memory -= next_process.get_size();

		if (DEBUG) cout << "DEBUG: (long_term_scheduler): allocated memory, available_memory now " << available_memory << endl;

		memory_allocate(next_process);

		// Remove the process from the NEW queue
		new_queue.erase(new_queue.begin());

        state_changed_string = "State changed for process " + next_process.get_string_id() + " changed from state " + next_process.get_state() + " to the READY state";

		// Change the process to READY and move to the READY queue
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
