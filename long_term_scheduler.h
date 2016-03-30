//============================================================================
// Name        : long_term_scheduler.h
// Author      :
// Version     : 0.01
// Description : Long term scheduling bringing processes into NEW and NEW->READY
//============================================================================

#ifndef LONG_TERM_SCHEDULER_H_
#define LONG_TERM_SCHEDULER_H_

#include "pcb.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <string>
using std::cout;
using std::cin;
using std::stringstream;
using std::basic_istream;
using std::basic_iostream;
using std::iostream;
using std::endl;
using std::vector;


/*
 * Some of these functions should go into another .cpp file
 * Right now this header file lumps together long_term and short_term
 * scheduling functions, which is bad form.
 */
void initialize_memory();
void new_process_arrival(PCB new_arrival);
void long_term_scheduler();

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
