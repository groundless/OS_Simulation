//============================================================================
// Name        : pcb.h
// Author      :
// Version     : 0.01
// Description : Main data structure for the Process Control Block
//============================================================================

#ifndef PCB_H_
#define PCB_H_

#include <string>
using std::string;

// Used for various debugging functions, set to false on release
#define DEBUG true

/*
 * Main class definition for the PCB. Requires more detailed
 * comments on each of the data members, which we can do after
 * we fully understand how they are being used.
 */
class PCB {

	/*
	 * Unique Identifier associated with the process
	 */
	int process_id;

	/*
	 * State can be the following:
	 * NEW / READY / RUNNING /
	 * BLOCKED / EXIT / NULL
	 */
	string state;

	/*
	 * Between 10 - 950 cycles of 0.1 seconds
	 */
	int total_runtime;

	/*
	 * Total time process has been running
	 */
	int elapsed_runtime;

	/*
	 * Between 0 - 5 requests
	 */
	int io_requests;

	/*
	 * Completed IO requests
	 */
	int io_completed;

	/*
	 * Size of process between 1mb and 8mb
	 */
	int size;

  public:

	/*
	 * Default constructor definition
	 */
	PCB ();

	/*
	 * Full constructor definition
	 */
	PCB (int, string, int, int, int, int, int);

	/*
	 * Return the total remaining IO requests left to complete.
	 */
    int iorequests_remaining() {return io_requests - io_completed;}

    /*
     * Return the total runtime left to complete the process.
     */
    int runtime_remaining() {return total_runtime - elapsed_runtime;}

    /*
     * Check if the current process state matches the argument state.
     */
    bool check_state(string check) {return (state == check);}

    /*
     * Returns the process_id
     */
    int get_id() {return process_id;}

    /*
     * Returns the process size
     */
    int get_size() {return size;}

    /*
     * Set the current process state to the argument state.
     * Must follow the convention defined above.
     */
    void set_state(string new_state) {state = new_state;}

    /*
     * Simulates process execution, increases elapsed_runtime by one.
     */
    void execute_instruction() {elapsed_runtime++;}

    /*
     * Simulates completion of an IO requests, increments io_completed.
     */
    void finish_iorequest() {io_completed++;}
};


#endif /* PCB_H_ */
