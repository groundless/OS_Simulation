//============================================================================
// Name		   : interrupts.cpp
// Author	   :
// Version	   :
// Description : Function declarations for the IO
//============================================================================

#include "io_requests.h"

int io_cycle_count = 0;

/*
 * Check for interrupts, including both IO requests as well as
 * interrupts from the short term scheduler because of time slicing.
 * An I/O operation takes somewhere between 25 to 50 cycles.
 * A time slice occurs every ten cycles.
 */
void check_io_interrupt () {

	// Check if the running process has any IO requests
	if (running_process.request_io()) {

		// Set the cycle count to a random number between 25 - 50 cycles
		// Simulates the cycle time required to process an IO request
		if (blocked_queue.empty())
			io_cycle_count = rand() % 25 + 25;

		if (DEBUG) cout << "DEBUG: (check_interupts): Running Process has an IO Request " << endl;

		// Indicate that the running process is now BLOCKED
		// Blocked processes remain in main memory
		running_process.set_state("BLOCKED");

		// Block running process while IO request is fulfilled
		blocked_queue.push_back(running_process);

		// Currently no running process, set running process to NULL
		PCB null_process;
		running_process = null_process;
		running_process.set_state("NULL");
	}

	// Check if the IO device is in use
	if (io_cycle_count > 0) {

		// Execute a cycle of the IO device
		io_cycle_count--;

		if (DEBUG) cout << "DEBUG: (check_interupts): io_cycle_count is " << io_cycle_count << endl;

		// Check if the IO has completed
		if (io_cycle_count == 0) {

			if (DEBUG) cout << "DEBUG: (check_interupts): IO Request Completed " << endl;
			if (DEBUG) cout << "DEBUG: (check_interupts): Process " << blocked_queue.front().get_id() << " has completed an IO Request " << endl;

			// Simulate completion of the IO request
			blocked_queue.front().finish_iorequest();

			// Move the process back onto the end of the Ready Queue
			// State change BLOCKED->READY
			ready_queue.push_back(blocked_queue.front());

			// Remove the process from the blocked queue
			blocked_queue.erase(blocked_queue.begin());

			// Check if there are still outstanding IO Requests
			if (!blocked_queue.empty()) {

				 // Reset the cycle count for the next IO request
				 io_cycle_count = rand() % 25 + 25;

				 if (DEBUG) cout << "DEBUG: (check_interupts): Resetting io_cycle_count to " << io_cycle_count << endl;
			}
		}
	}
}


