//============================================================================
// Name		   : state_queues.h
// Description : Main queue definitions for the five states of the process model.
//============================================================================

#ifndef STATE_QUEUES_H_
#define STATE_QUEUES_H_

#include "pcb.h"

// Main preprocessor definition of the memory size of the RAM
// Represents 16 megabytes.
#define MEM_SIZE 16

// main_memory array contains sixteen indexes, each representing
// one megabyte of memory. Each index will contain the process_id
// of the process occupying that megabyte of memory.
extern int main_memory[MEM_SIZE];

// Primary vectors of PCBs for the NEW and READY queue.
extern std::vector<PCB> new_queue;
extern std::vector<PCB> ready_queue;

// Blocked queue for processes waiting on IO.
extern std::vector<PCB> blocked_queue;

// List of processes that have completed. Currently not used.
// Stores the history of processes in the OS.
extern std::vector<PCB> finished_list;

// The currently running process.
extern PCB running_process;

// Boolean flag used to halt the OS when a process state has changed.
// The flag is set to true for each of the following cases:
// a new process enters the system,
// a processes state changes,
// an I/O request is made,
// an I/O request is completed,
// memory is allocated or deallocated,
// a process exits the system.
extern bool state_changed_flag;

// String which is used to store a description of what state has changed.
// Primarily used to display to the user what has changed.
extern string state_changed_description;

#endif /* STATE_QUEUES_ */
