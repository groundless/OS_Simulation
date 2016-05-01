//============================================================================
// Name		   : io_requests.cpp
// Description : Functions related to the processing of IO requests.
//============================================================================

#include "io_requests.h"

int io_cycle_count = 0;

// The list of the simulated IO devices currently in use.
// Each entry refers to an IO device which is currently satisfying
// the IO request from a process. The location in the vector mirrors
// the location of the process in the block_queue. i.e. If only one entry
// is currently in the io_devices_active, then only one IO device is currently
// satisfying a request for a single process in the blocked_queue.
// NOTE: The simulation is capable of supporting multiple concurrent IO devices.
// Such that many processes can currently and simultaneously be working with an
// associated IO device per execution cycle.
std::vector<int> io_devices_active;


// Check for interrupts, including both IO requests as well as
// interrupts from the short term scheduler because of time slicing.
// An I/O operation takes somewhere between 25 to 50 cycles.
// A time slice occurs every ten cycles.
void check_io_interrupt () {

	// Check if the running process has any IO requests
	if (running_process.request_io()) {

		if (DEBUG) cout << "DEBUG: (check_interupts): Running Process has an IO Request " << endl;

		// Indicate that the running process is now BLOCKED
		// Blocked processes remain in main memory
		running_process.set_state("BLOCKED");

		// Block running process while IO request is fulfilled
		blocked_queue.push_back(running_process);

		// Activate an IO device (i.e. push a counter onto the active device list)
		// Set the cycle count to a random number between 25 - 50 cycles
		// Simulates the cycle time required to process an IO request
		io_cycle_count = rand() % 25 + 25;
		io_devices_active.push_back(io_cycle_count);

		 // Process has an IO request, and the state has changed from
		 // RUNNING to BLOCKED. Update the display.
		state_changed_flag = true;
		stringstream ss;
		ss << "Process [" << running_process.get_id() << "] has an IO request and has moved from Running to Blocked.";
		state_changed_description = ss.str();

		// Currently no running process, set running process to NULL
		PCB null_process;
		running_process = null_process;
		running_process.set_state("NULL");
	}
}

void process_io_devices() {

	// Check if any IO devices are currently active
	if (!io_devices_active.empty()) {

		// Iterate through the list of active IO devices
		for (unsigned int i = 0; i < io_devices_active.size(); i++) {

			// Each IO device decreases its counter until finished, for every execution cycle.
			io_devices_active.at(i)--;

			if (DEBUG) cout << "DEBUG: (process_io_devices): Process " << blocked_queue.at(i).get_id() << " has " << io_devices_active.at(i) << " IO cycles left until completion." << endl;

			// Now check if the IO device has completed
			if (io_devices_active.at(i) == 0) {

				if (DEBUG) cout << "DEBUG: (process_io_devices): IO request has been completed for process " << endl;

				// Simulate completion of the IO request
				blocked_queue.at(i).finish_iorequest();

				// Move the process back onto the end of the Ready Queue
				// State change BLOCKED->READY
				ready_queue.push_back(blocked_queue.at(i));

				// IO Request has been completed, and the process state has changed
				// from BLOCKED to READY.
				state_changed_flag = true;
				stringstream ss;
				ss << "Process [" << blocked_queue.at(i).get_id() << "] has completed an IO request and has moved from Blocked to Ready.";
				state_changed_description = ss.str();

				// Remove the process from the blocked queue
				blocked_queue.erase(blocked_queue.begin() + i);
				// Remove the IO device from the active list
				io_devices_active.erase(io_devices_active.begin() + i);
			}
		}
	}
	else
	{
		if (DEBUG) cout << "DEBUG: (process_io_devices): No IO devices active " << endl;
	}
}


