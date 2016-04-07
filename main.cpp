//============================================================================
// Name        : main.cpp
// Author      :
// Version     : 0.03
// Description : Main OS
//============================================================================

#include "long_term_scheduler.h"
#include "short_term_scheduler.h"


// Temporary list of processes simulating arrival.
std::vector<PCB> process_list;

/*
 * Temporary debugging processes coming into the OS
 */
void debug_input_processing() {
	int num_processes = 10;
	int size_min = 1;
	int size_max = 8;
	//int arrival_min = 10;
	//int arrival_max = 100;
	int runtime_min = 1;
	int runtime_max = 100;
	int io_min = 0;
	int io_max = 5;

	srand(time(NULL));

	int index;
	for (index = 0; index < num_processes; index++) {
		PCB next_process(
				rand() % 99 + 1,
				"NEW",
				rand() % runtime_max + runtime_min,
				0,
				io_max,
				io_min,
				rand() % size_max + size_min);
		process_list.push_back(next_process);
	}
}

PCB retrieve_next_process () {
	PCB next_process;
	next_process.set_state("NULL");
	if (process_list.empty()) {
		if (DEBUG){cout << "Process list is empty" << endl;}
		return next_process;
	}
	next_process = process_list.back();
	process_list.pop_back();
	return next_process;
}

int main(void)
{

	/*
	 * Initially read in inputs and build processes
	 * Run long term scheduler to put a few processes into NEW
	 * Allocate memory for processes in NEW to put into READY
	 * Run short term scheduler to bring a process from READY->RUNNING
	 * Loop time cycles and process interrupts
	 */

	initialize_memory();

	/*
	 * Two input processing options, one is manual and the other
	 * auto-generates processes for ease of testing.
	 */

	//begin_input_processing();
	debug_input_processing();

	/*
	 * Initial process arrival, the OS always starts with something running?
	 * This potentially simplifies the main loop and makes the fetch-execute-interrupt
	 * logic more apparent.
	 */

	new_process_arrival(retrieve_next_process());


	/* Fetch-execute-interrupt begins
	 * Wait 0.1 seconds to simulate the cycle
	 * Process in RUN executes for a 0.1 cycle
	 * Check for interrupts or preemption
	 * If process is EXIT then run short term scheduler
	 */

	/*
	 * The main do while loop for the program, which exits when the user inputs
	 * 'exit' as a string to end the program. The string input is the main string
	 * for processing user input, and cycle_count is a counter for how many cycles
	 * have been looped.
	 */

	string input = "";
	int cycle_count = 0;

	do {

		/*
		 * Check if any new processes have arrived first.
		 * If no processes have arrived, only passes a NULL reference.
		 */
		new_process_arrival(retrieve_next_process());

		/*
		 * Long term FCFS scheduler
		 * Simulates process arrival.
		 */
		long_term_scheduler();

		/*
		 * Short term preemptive scheduler.
		 * Needs to be implemented!
		 */
		short_term_scheduler();

		// Increase cycle count of the fetch-execute-interrupt cycle
		cycle_count++;

		// Run the current process in the RUNNING state
		execute_running_process();

		// Check for interrupts and preemption
		check_interrupts();

		// Debugging print for the new and ready queues
		debug_print_new_ready();


		// User interaction
		cout << "Type 'exit' to exit the program:\n";
		cout << "Press enter to advance one clock cycle (this is temporary):\n>";
		getline(cin, input);
		// User echo initially to make sure we are reading input correctly.
		cout << "You entered: " << input << endl << endl;

	} while (input != "exit");

	cout << "System exiting\n";
	// User must press a key to exit
	getline(cin, input);

	return 0;
}
