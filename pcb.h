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

	// Completed IO requests
	int io_completed;

	// Between 1mb and 8mb
	int size;

}PCB;

/*
class PCB {
	int process_id;
	string state;
	int total_runtime;
	int elapsed_runtime;
	int io_requests;
	int io_completed;
	int size;
  public:
    int iorequests_remaining() {return io_requests - io_completed;}
    int runtime_remaining() {return total_runtime - elapsed_runtime;}
    bool check_state(string check) {return (state == check);}
    int get_id() {return process_id;}
    int get_size() {return size;}
};
*/

#endif /* PCB_H_ */
