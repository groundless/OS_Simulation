//============================================================================
// Name        : pcb.h
// Description : Primary class definition for the Process Control Block.
//               Contains both a default constructor, and an extended constructor.
//               Top header file in the include hierarchy, thus this header
//               includes the necessary libraries used throughout the OS.
//============================================================================

#ifndef PCB_H_
#define PCB_H_

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using std::string;
using std::cout;
using std::cin;
using std::stringstream;
using std::basic_istream;
using std::basic_iostream;
using std::iostream;
using std::ifstream;
using std::endl;
using std::getline;
using std::istringstream;

// Used for various debugging functions, set to false on release.
// Setting to true will only function with the debugging UI.
#define DEBUG false

class PCB {

	// Unique Identifier associated with the process
	int process_id;

	// State can be the following:
	// NEW / READY / RUNNING /
	// BLOCKED / EXIT / NULL
	string state;

	// Counter for the number of cycles the process while running
	// has executed while in the RUNNING state. If the counter has
	// reached TEN, indicating the maximum cycles for a time slice,
	// then the time slice for the current process has ended.
	int scheduling_counter;

	// Between 10 - 950 cycles
	int total_runtime;

	// Total time the process has been running
	int elapsed_runtime;

	// Between 0 - 5 requests
	int io_requests;

	// Completed IO requests
	int io_completed;

	// Size of process between 1mb and 8mb
	int size;

  public:

	// Default constructor definition
	PCB ();

	// Full constructor definition
	PCB (int, string, int, int, int, int, int);

	// Return the total remaining IO requests left to complete.
    int iorequests_remaining() {return io_requests - io_completed;}

    // Return the total runtime left to complete the process.
    int runtime_remaining() {return total_runtime - elapsed_runtime;}

    // Check if the current process state matches the argument state.
    bool check_state(string check) {return (state == check);}

    // Returns the process_id
    int get_id() {return process_id;}

    // Returns the process size
    int get_size() {return size;}

    // Returns the number of cycles executed for the current time slice.
    int get_scheduling_counter() {return scheduling_counter;}

    // Returns the elapsed runtime
    int get_elapsed_runtime() {return elapsed_runtime;}

    // Returns IO requests satisfied
    int get_io_completed() {return io_completed;}

    // Set the current process state to the argument state.
    // Must follow the convention defined above.
    void set_state(string new_state) {state = new_state;}

    // Increases the counter for the current number of cycles in the time slice.
    void increment_scheduling_counter() {scheduling_counter++;}

    // Resets the scheduling counter to zero, for when the time slice has ended.
    void reset_scheduling_counter() {scheduling_counter = 0;}

    // Simulates process execution, increases elapsed_runtime by one.
    void execute_instruction() {elapsed_runtime++;}

    // Simulates completion of an IO requests, increments io_completed.
    void finish_iorequest() {io_completed++;}

    // Simulates an IO request based on how may IO requests remain,
    // and the total runtime that the process has been running.
    bool request_io() {
    	if ((io_requests - io_completed) == 0) return false;
    	return ((total_runtime / ((io_requests - io_completed) + 1)) < elapsed_runtime);
    }
};

// Default constructor for the PCB
inline PCB::PCB () {
	process_id = -1;
	state = "NULL";
	scheduling_counter = 0;
	total_runtime = 0;
	elapsed_runtime = 0;
	io_requests = 0;
	io_completed = 0;
	size = 0;
}

// Detailed constructor for PCB, needs all the information.
inline PCB::PCB (int id, string s,
		  int tr, int er,
		  int ior, int ioc,
		  int sz) {
	process_id = id;
	state = s;
	scheduling_counter = 0;
	total_runtime = tr;
	elapsed_runtime = er;
	io_requests = ior;
	io_completed = ioc;
	size = sz;
}

#endif /* PCB_H_ */
