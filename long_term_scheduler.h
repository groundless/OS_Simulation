//============================================================================
// Name        : long_term_scheduler.h
// Author      :
// Version     : 0.01
// Description : Long term scheduling bringing processes into NEW and NEW->READY
//============================================================================

#ifndef LONG_TERM_SCHEDULER_H_
#define LONG_TERM_SCHEDULER_H_

#include "state_queues.h"

void initialize_memory();
void new_process_arrival(PCB new_arrival);
void long_term_scheduler();
void execute_running_process();
void process_exit();
void check_interrupts();


/*
 * Debugging functions.
 * Just how many of these will appear is yet to be seen.
 */
void debug_print_new_ready();


#endif /* LONG_TERM_SCHEDULER_H_ */
