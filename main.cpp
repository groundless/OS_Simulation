//============================================================================
// Name        : main.cpp
// Author      :
// Version     : 0.03
// Description : Main OS
//============================================================================

#include "io_requests.h"
#include "long_term_scheduler.h"
#include "short_term_scheduler.h"
#include "output_ui.h"
#include "process_arrival.h"

/*
 * Flag which indicates whether we are allowing the OS
 * to run to completion, i.e. slowly display the state
 * changes of the processes as the OS functions.
 */
bool run_to_completion = true;

void hold_on_state_change() {
	string input;
	if (state_changed_flag && !run_to_completion) {
		clear_console();
		debug_print();
		cout << "State has changed" << endl;
		cout << "Press any key to continue: or type 'run' to run to completion." << endl;
		getline(cin, input);
		state_changed_flag = false;
		if (input == "run") run_to_completion = true;
	}
}

int main(void)
{
	srand(time(NULL));

	/*
	 * Creates a stream and checks to see if the Processes.txt file exists.
	 * If it doesn't, the program returns an error and will exit.
	*/
	
	ifstream inputProcesses;
	inputProcesses.open("Processes.txt");
	while(!inputProcesses.is_open()) {
		cout << "ERROR: file Process.txt can not be opened. Please check that Process.txt is in the correct folder." << endl;
		exit(0);
	}
	
	//Checks the Processes.txt file for any errors in formatting

	check_file(inputProcesses);
	
	initialize_console();
	/*
	 * Initially read in inputs and build processes
	 * Run long term scheduler to put a few processes into NEW
	 * Allocate memory for processes in NEW to put into READY
	 * Run short term scheduler to bring a process from READY->RUNNING
	 * Loop time cycles and process interrupts
	 */

	initialize_memory();

	/*
	 * Initial process arrival, the OS always starts with something running?
	 * This potentially simplifies the main loop and makes the fetch-execute-interrupt
	 * logic more apparent.
	 */

	new_process_arrival(retrieve_next_process(inputProcesses));


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

	/*
	 * Do we want to initially run to completion?
	 * NOTE: This position will change, we will want to
	 * allow the user to change this at ANY POINT.
	 */
	/*
	cout << "Run OS to completion? (y or n):\n";
	getline(cin, input);

	// Temporary Logic and Display, CHANGE LATER
	if (input == "y") run_to_completion = true;
	else if (input == "n") run_to_completion = false;
	else cout << "Wrong input: run_to_completion is false";

	// User echo initially to make sure we are reading input correctly.
	cout << "You entered: " << input << endl << endl;
	cout << "BEGINNING SIMULATION" << endl;
	*/

	do {

		/*
		 * Check if any new processes have arrived first.
		 * If no processes have arrived, only passes a NULL reference.
		 */
		new_process_arrival(retrieve_next_process(inputProcesses));; hold_on_state_change();

		/*
		 * Long term FCFS scheduler
		 * Simulates process arrival.
		 */
		long_term_scheduler(); hold_on_state_change();

		/*
		 * Short term preemptive scheduler.
		 * Implemented as Round Robin with a 10 cycle time slice.
		 */
		short_term_scheduler(); hold_on_state_change();

		// Increase cycle count of the fetch-execute-interrupt cycle
		cycle_count++;

		// Run the current process in the RUNNING state
		execute_running_process();

		// Check for any interrupts
		check_io_interrupt(); hold_on_state_change();

		// Check active IO devices
		process_io_devices(); hold_on_state_change();

		// Debugging print for the new and ready queues

		debug_print();

		// User interaction
		cout << "Type 'exit' to exit the program:\n";
		cout << "Press enter to advance one clock cycle (this is temporary):\n>";

		if(run_to_completion != true){
            getline(cin, input);
		}
		else if(new_queue.empty() && blocked_queue.empty() && running_process.check_state("NULL") && ready_queue.empty()){ // Also check if simulation is finished. If file is empty, and all queues are empty.
            //Sleep for 2000 milliseconds
            cout << "Simulation has finished" << endl;
            input = "exit";

		}
        else{

            Sleep(2000);
        }

		// User echo initially to make sure we are reading input correctly.
		cout << "You entered: " << input << endl << endl;

		clear_console();

	} while (input != "exit");

	cout << "System exiting\n";
	// User must press a key to exit
	getline(cin, input);

	return 0;
}

