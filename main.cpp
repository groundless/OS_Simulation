//============================================================================
// Name        : main.cpp
// Author      :
// Version     : 0.02
// Description : Main OS
//============================================================================
#include <iostream>
#include <string>
#include "long_term_scheduler.h"
#include "input_processing.h"

// This must change once all the headers are compiled
// Generally bad form to just include all of std.
using namespace std;

// Probably unnecessary print and swap functions
// void print_array(int* array, int n);
// void swap(int &a, int &b);

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

		/* Check if any new processes have arrived first.
		 * Pass the next process from input_processing to long_term_scheduler
		 * If no processes have arrived, only passes a NULL reference.
		 */

		new_process_arrival(retrieve_next_process());

		/*
		 * Short term preemptive scheduler.
		 * Needs to be implemented!
		 */

		short_term_scheduler();

		// Increase cycle count of the fetch-execute-interrupt cycle
		cycle_count++;

		// Run the current process in the RUNNING state
		execute_running_process();

		// Check for interrupts and preemption, possibly:
		// check_interrupts() or preempt_process();

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

/*
void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void print_array(int* array, int n)
{
	int i;
	for(i = 0; i < n; i++)
		cout << array[i] << '\t';
}
*/
