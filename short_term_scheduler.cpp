//============================================================================
// Name        : short_term_scheduler.cpp
// Author      :
// Version     : 0.01
// Description : Short term scheduling bringing processes READY to RUNNING
//============================================================================

#include "long_term_scheduler.h"
#include "short_term_scheduler.h"

/*
 * Counter for the number of cycles the current running process
 * has executed while in the RUNNING state. If the counter has
 * reached TEN, indicating the maximum cycles for a time slice,
 * then preemption is necessary and an interrupt is issued.
 */
int round_robin_counter = 0;

/*
 * "The short-term scheduler, also known as the dispatcher, executes most frequently
 * and makes the fine-grained decisions of which process to execute next. The short-term
 * scheduler is invoked whenever an event occurs that may lead to the blocking of the current
 * process or that may provide an opportunity to preempt a currently running process in favor
 * of another. Examples include - Clock Interrupts - I/O Interrupts" pg. 402 Stallings.
 */
void short_term_scheduler () {

	// Check if there is no process currently running
	if (running_process.check_state("NULL")) {

		if (DEBUG) cout << "DEBUG: (short_term_scheduler): no process currently running" << endl;

		// Check if the ready queue is empty
		if (ready_queue.empty()) {

			if (DEBUG) cout << "DEBUG: (short_term_scheduler): Ready Queue is currently empty" << endl;

			// Check if the new queue is empty, only necessary for debugging.
			// Long term scheduler will eventually put a process into the new/ready queue.
			if (new_queue.empty())
				if (DEBUG) cout << "DEBUG: (short_term_scheduler): New Queue is also currently empty" << endl;

			// Nothing to run, short term scheduler did nothing.
			return;
		}
		else {

			// Get the next process from the ready queue
			running_process = ready_queue.front();

			// Remove that process from the front of the ready queue
			ready_queue.erase(ready_queue.begin());

			// Reset the time slice counter, this could happen because the previous process was BLOCKED.
			round_robin_counter = 0;

			if (DEBUG) cout << "DEBUG: (short_term_scheduler): put process: " << running_process.get_id() << " into running" << endl;

			// A process has changed from READY to RUNNING, update the UI.
			state_changed_flag = true;
		}
	}
	else {

		// A process is already running
		if (DEBUG) cout << "DEBUG: (short_term_scheduler): Current running process ID is :" << running_process.get_id() << endl;

		// Increment the counter for the current process time slice
		round_robin_counter++;

		if (DEBUG) cout << "DEBUG: (short_term_scheduler): time slice counter is: " << round_robin_counter << endl;

		// Ten is the maximum number of cycles for a time slice
		if (round_robin_counter == 10){

			// Should we issue an interrupt? (This would be more in line with a real OS)
			ready_queue.push_back(running_process);

			// Set running_process to null;
			PCB null_process;
			running_process = null_process;
			running_process.set_state("NULL");

			// Restart the scheduler?
			// Maybe this should wait until next clock cycle?
			short_term_scheduler();
		}

		// Check if that process has finished yet
		// Redundant check? This happens in the execute_running_process() function
		// this may never actually execute, CHECK THIS DURING DEBUGGING
		if (running_process.runtime_remaining() == 0) {
			if (DEBUG) cout << "DEBUG: (short_term_scheduler): Running Process has finished " << endl;

			// The finished process now goes from READY->EXIT
			process_exit();
		}
	}
}
