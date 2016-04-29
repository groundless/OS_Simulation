//============================================================================
// Name		   : state_queues.h
// Author	   :
// Version	   :
// Description : Main queue definitions for the five states of the processes
//============================================================================

#ifndef STATE_QUEUES_H_
#define STATE_QUEUES_H_

#include "pcb.h"

/*
 * Main preprocessor definition of the memory size of the RAM
 */
#define MEM_SIZE 16

/*
 * main_memory array contains sixteen indexes, each representing
 * one megabyte of memory. Each index will contain the process_id
 * of the process occupying that megabyte of memory.
 */
extern int main_memory[MEM_SIZE];

/*
 * Primary vectors of PCBs for the NEW and READY queue.
 */
extern std::vector<PCB> new_queue;
extern std::vector<PCB> ready_queue;

/*
 * Blocked queue for processes waiting on IO
 */
extern std::vector<PCB> blocked_queue;

/*
 * List of processes that have completed. May not be needed.
 * But used anyway to store the history of processes in the OS.
 */
extern std::vector<PCB> finished_list;

/*
 * The main running process.
 */
extern PCB running_process;


/*
 * boolean flag used to halt when a process state has changed.
 * implemented in accordance with the project specifications:
 *
 * "display should change each time one of the following occurs:
 * a new process enters the system,
 * a processes state changes,
 * an I/O request is made,
 * an I/O request is completed,
 * memory is allocated or deallocated,
 * or a process exits the system."
 */
extern bool state_changed_flag;

extern string state_changed_string;

#endif /* STATE_QUEUES_ */
