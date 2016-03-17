//============================================================================
// Name        : input_processing.h
// Author      :
// Version     : 0.01
// Description : Header file for the input processing program
//============================================================================


#ifndef INPUT_PROCESSING_H_
#define INPUT_PROCESSING_H_

#include "pcb.h"

#include <iostream>
#include <sstream>
using std::cout;
using std::cin;
using std::stringstream;
using std::basic_istream;
using std::basic_iostream;
using std::iostream;
using std::endl;

void begin_input_processing();
void input_total_processes();
void input_process_size();
void input_arrival_interval();
void input_runtime_interval();

void build_process_list();
PCB retrieve_next_process();

void debug_input_processing();

#endif /* INPUT_PROCESSING_H_ */
