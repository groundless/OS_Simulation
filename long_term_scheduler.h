//============================================================================
// Name        : long_term_scheduler.h
// Description : Contains functions for the long term scheduler, memory
//               management, process execution, process arrival and exiting.
//============================================================================

#ifndef LONG_TERM_SCHEDULER_H_
#define LONG_TERM_SCHEDULER_H_

#include "state_queues.h"

void initialize_memory();
void new_process_arrival(PCB new_arrival);
void long_term_scheduler();
void execute_running_process();
void process_exit();

#endif /* LONG_TERM_SCHEDULER_H_ */
