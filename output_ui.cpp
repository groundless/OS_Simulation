//============================================================================
// Name		   : interrupts.cpp
// Author	   :
// Version	   :
// Description : Function declarations for the IO
//============================================================================

#include "output_ui.h"

/*
 * Debugging function, prints out the processes in the NEW and READY queue.
 */
void debug_print_new_ready () {
	unsigned int index;
	if (DEBUG) {
		cout << "DEBUG: New Queue size is " << new_queue.size() << endl;
		for (index = 0; index < new_queue.size(); index++) {
			cout << "DEBUG: New Queue - Process " << new_queue.at(index).get_id() << " size is: " << new_queue.at(index).get_size() << endl;
		}
		cout << "DEBUG: Ready Queue size is " << ready_queue.size() << endl;
		for (index = 0; index < ready_queue.size(); index++) {
			cout << "DEBUG: Ready Queue -  Process " << ready_queue.at(index).get_id() << " size is: " << ready_queue.at(index).get_size() << endl;
		}
		cout << "DEBUG: Blocked Queue size is " << blocked_queue.size() << endl;
		for (index = 0; index < blocked_queue.size(); index++) {
			cout << "DEBUG: Blocked Queue -  Process " << blocked_queue.at(index).get_id() << " size is: " << blocked_queue.at(index).get_size() << endl;
		}
		if (!running_process.check_state("NULL")) {
			cout << "DEBUG: Running Process - " << running_process.get_id() << " size is " << running_process.get_size() << endl;
		}
	}
}

/*
 * Print out the main_memory array visually.
 * For debugging purposes.
 */
void debug_print_memory() {
	if (DEBUG) {
		for (int i = 0; i < MEM_SIZE; i++) {
			cout << "Main Memory " << i << ": PID " << main_memory[i] << endl;
		}
	}
}
