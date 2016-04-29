//============================================================================
// Name        : main.cpp
// Description : Main OS Simulation file.
//============================================================================

#include "io_requests.h"
#include "long_term_scheduler.h"
#include "short_term_scheduler.h"
#include "output_ui.h"



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

/*
 * Flag which indicates whether we are allowing the OS
 * to run to completion, i.e. slowly display the state
 * changes of the processes as the OS functions.
 */
bool run_to_completion = false;
/*
 * Step indicates the number of seconds to sleep between
 * states updating. User specified.
 */
int step = 0;

void hold_on_state_change() {
	string input;
	if (state_changed_flag && !run_to_completion) {
		display_ui();
		cout << "Press the enter key to continue, or type 'run' to run to completion. " << endl;
		getline(cin, input);
		state_changed_flag = false;
		if (input == "run"){
            run_to_completion = true;
            cout << "How many seconds between each step? Enter a positive integer: ";
            cin >> step;
            cin.ignore(1000, '\n');
		}
		else if (input == "exit") {
			exit(0);
		}
	}
    else if (state_changed_flag && run_to_completion) {
		display_ui();
		state_changed_flag = false;
		Sleep(step*1000);
	}
}

int main(void)
{
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
	 * Temporary debugging process generation
	 * See the above functions
	 */

	debug_input_processing();

	/*
	 * Initial process arrival, the OS always starts with something running?
	 * This potentially simplifies the main loop and makes the fetch-execute-interrupt
	 * logic more apparent.
	 */

	new_process_arrival(retrieve_next_process());

	string input = "";
	int cycle_count = 0;

	do {

		// Check if any new processes have arrived first. If no processes have arrived, only passes a NULL reference.
		new_process_arrival(retrieve_next_process()); hold_on_state_change();

		// Long term scheduler. Implemented as First Come First Serve.
		long_term_scheduler(); hold_on_state_change();

		// Short term preemptive scheduler. Implemented as Round Robin with a 10 cycle time slice.
		short_term_scheduler(); hold_on_state_change();

		// Increase cycle count to keep track of the number of cycles executed.
		cycle_count++;

		// Run the current process in the RUNNING state.
		execute_running_process(); hold_on_state_change();

		// Check for any interrupts from the currently running process.
		check_io_interrupt(); hold_on_state_change();

		// Check active IO devices
		process_io_devices(); hold_on_state_change();

		// Check if the simulation is finished. If process file is empty, and all queues are empty.
		if (new_queue.empty() && blocked_queue.empty() && running_process.check_state("NULL") && ready_queue.empty()) {
            cout << "OS Simulation has finished" << endl;
            input = "exit";
		}

	} while (input != "exit");

	hold_on_state_change();
	cout << "Press any key to exit" << endl;
	getline(cin, input);
	return 0;
}
