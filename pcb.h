//============================================================================
// Name        : pcb.h
// Author      :
// Version     : 0.01
// Description : Main data structure for the Process Control Block
//============================================================================

#ifndef PCB_H_
#define PCB_H_

#include <string>
#include <vector>
using std::string;
using std::vector;

// Used for various debugging functions, set to false on release
#define DEBUG true

typedef struct
{
	// Unique Identifier associated with the process
	int process_id;

	// State can be the following:
	// NEW / READY / RUNNING / BLOCKED / EXIT / NULL
	string state;

	// Between 10 - 950 cycles of 0.1 seconds
	int total_runtime;

	// Total time process has been running
	int elapsed_runtime;

	// Between 0 - 5 requests
	int io_requests;

	// Between 1mb and 8mb
	int size;

}PCB;

#endif /* PCB_H_ */
