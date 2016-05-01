//============================================================================
// Name        : short_term_scheduler.cpp
// Description : Short term scheduling bringing processes READY to RUNNING
//============================================================================

#include "long_term_scheduler.h"
#include "short_term_scheduler.h"

// "The short-term scheduler, also known as the dispatcher, executes most frequently
// and makes the fine-grained decisions of which process to execute next. The short-term
// scheduler is invoked whenever an event occurs that may lead to the blocking of the current
// process or that may provide an opportunity to preempt a currently running process in favor
// of another. Examples include - Clock Interrupts - I/O Interrupts" pg. 402 Stallings.

void short_term_scheduler () {

	if (running_process.check_state("NULL")) {
		if (DEBUG) cout << "DEBUG: (short_term_scheduler): no process currently running" << endl;

		if (ready_queue.empty()) {
			if (DEBUG) cout << "DEBUG: (short_term_scheduler): Ready Queue is currently empty" << endl;

			// Only necessary for debugging, long term scheduler will eventually put a process into the new/ready queue.
			if (new_queue.empty())
				if (DEBUG) cout << "DEBUG: (short_term_scheduler): New Queue is also currently empty" << endl;

			// Both the ready queue and the new queue are empty,
			// the short term scheduler did nothing.
			return;
		}
		else {
			// The ready queue has processes waiting to run,
			// first get the next process from the ready queue.
			running_process = ready_queue.front();

			// A process has changed from READY to RUNNING.
			state_changed_flag = true;
			stringstream ss;
			if (running_process.get_id() == ready_queue.back().get_id() && running_process.get_scheduling_counter() == 10)
				ss << "The time slice for Process [" << running_process.get_id() << "]" << " has ended. \n"
				   << "No preemption occurs. Process [" << running_process.get_id() << "] remains in Running.";
			else
				ss << "Process [" << running_process.get_id() << "] has moved from Ready to Running.";
			state_changed_description = ss.str();

			// Remove that process from the front of the ready queue
			ready_queue.erase(ready_queue.begin());

			if (DEBUG) cout << "DEBUG: (short_term_scheduler): put process: " << running_process.get_id() << " into running" << endl;

			// Reset the time slice counter, this could also happen because the previous process was BLOCKED.
			running_process.reset_scheduling_counter();
		}
	}
	// A process is already running.
	else {

		if (DEBUG) cout << "DEBUG: (short_term_scheduler): Current running process ID is :" << running_process.get_id() << endl;

		// Increment the counter for the current process time slice.
		running_process.increment_scheduling_counter();

		if (DEBUG) cout << "DEBUG: (short_term_scheduler): time slice counter is: " << running_process.get_scheduling_counter() << endl;

		// Ten is the maximum number of cycles for a time slice.
		// Preemption now occurs, moving the current running process back to ready.
		// The short term scheduler now runs again.
		if (running_process.get_scheduling_counter() == 10){

			ready_queue.push_back(running_process);

			// Set the current running process to NULL.
			PCB null_process;
			running_process = null_process;
			running_process.set_state("NULL");

			short_term_scheduler();
		}

		// Check if that process has finished yet
		// Redundant check? This happens in the execute_running_process() function
		// this may never actually execute, CHECK THIS DURING DEBUGGING
		if (running_process.runtime_remaining() == 0) {
			if (DEBUG) cout << "DEBUG: (short_term_scheduler): Running Process has finished " << endl;
			if (DEBUG) cout << "DEBUG: SHORT TERM SCHEDULER IS DOING READY->EXIT?" << endl;

			exit (EXIT_FAILURE);

			// The finished process now goes from READY->EXIT
			process_exit();
		}
	}
}
