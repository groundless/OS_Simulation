//============================================================================
// Name        : short_term_scheduler.cpp
// Author      :
// Version     : 0.01
// Description : Short term scheduling bringing processes READY to RUNNING
//============================================================================

#include "long_term_scheduler.h"
#include "short_term_scheduler.h"


/*
 * Basically FCFS temporarily, also not fully working.
 * This should make use of debug statements, since getting a good implementation
 * working that we also know is working will take some time.
 */
void short_term_scheduler () {

	// Check if there is no process currently running
	if (running_process.check_state("NULL")) {

		if (DEBUG) cout << "DEBUG: (short_term_scheduler): no process currently running" << endl;

		// Check if the ready queue is empty
		if (ready_queue.empty()) {

			if (DEBUG) cout << "DEBUG: (short_term_scheduler): Ready Queue is currently empty" << endl;

			// Check if the new queue is empty
			if (new_queue.empty()) {

				if (DEBUG) cout << "DEBUG: (short_term_scheduler): New Queue is also currently empty" << endl;

				// Do nothing? Long term scheduler will eventually put a process into the new/ready queue?
			}

			// Nothing to run, short term scheduler did nothing.
			return;
		}

		// Get the next process from the ready queue
		running_process = ready_queue.front();

		// Remove that process from the front of the ready queue
		ready_queue.erase(ready_queue.begin());

		if (DEBUG) cout << "DEBUG: (short_term_scheduler): put process: " << running_process.get_id() << " into running" << endl;
	}
	else {

		// A process is already running
		if (DEBUG) cout << "DEBUG: (short_term_scheduler): Current running process ID is :" << running_process.get_id() << endl;

		// Check if that process has finished yet
		if (running_process.runtime_remaining() == 0) {
			if (DEBUG) cout << "DEBUG: (short_term_scheduler): Running Process has finished " << endl;

			// The finished process now goes from READY->EXIT
			process_exit();
		}
	}
}
