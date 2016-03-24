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
 * Some of these functions should go into another .cpp file
 * Right now this header file lumps together long_term and short_term
 * scheduling functions, which is bad form.
 */
void initialize_memory();
void new_process_arrival(PCB new_arrival);
void allocate_memory();

void execute_running_process();
void short_term_scheduler();
void process_exit();
void check_interrupts();


/*
 * Debugging functions.
 * Just how many of these will appear is yet to be seen.
 */
void debug_print_new_ready();


#endif /* LONG_TERM_SCHEDULER_H_ */
