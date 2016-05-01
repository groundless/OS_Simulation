//==================================================================================
// Name        : main.cpp
// Description : Main Operating System Simulation file.
//==================================================================================

#include "process_arrival.h"
#include "long_term_scheduler.h"
#include "short_term_scheduler.h"
#include "io_requests.h"
#include "output_ui.h"

int main(void)
{
	string input = "";

	// Counts the number of cycles the operating system runs for.
	int cycle_count = 0;

	// Creates a stream and checks if the Processes.txt file exists.
	// If it doesn't, the program returns an error and will exit.
	ifstream inputProcesses;
	inputProcesses.open("Processes.txt");
	while (!inputProcesses.is_open()) {
		cout << "ERROR: The file Process.txt cannot be opened. Please check that Process.txt is in the same folder." << endl;
		getline(cin, input);
		exit(0);
	}

	// Checks the Processes.txt file for any errors in formatting.
	check_file(inputProcesses);

	// Resize and move the console display window.
	initialize_console();

	// Basic initializations within the OS.
	initialize_memory();

	do {
		// Check if any new processes have arrived first. Pulls process info from Processes.txt
		new_process_arrival(retrieve_next_process(inputProcesses)); hold_on_state_change();

		// Long term scheduler. Implemented as First Come First Serve.
		long_term_scheduler(); hold_on_state_change();

		// Short term preemptive scheduler. Implemented as Round Robin with a 10 cycle time slice.
		short_term_scheduler(); hold_on_state_change();

		// Increase cycle count to keep track of the number of cycles executed by the operating system.
		cycle_count++;

		// Run the current process in the running state.
		execute_running_process(); hold_on_state_change();

		// Check for any interrupts from the currently running process.
		check_io_interrupt(); hold_on_state_change();

		// Check active IO devices
		process_io_devices(); hold_on_state_change();

		// Check if the simulation is finished. If the Processes.txt file is empty, and all queues are empty.
		if (new_queue.empty() && blocked_queue.empty()
							  && running_process.check_state("NULL")
							  && ready_queue.empty()
							  && inputProcesses.eof()) {
            cout << "OS Simulation has finished, after " << cycle_count << " cycles." << endl;
            input = "exit";
		}

	} while (input != "exit");

	hold_on_state_change();
	cout << "Press any key to exit" << endl;
	getline(cin, input);
	return 0;
}
