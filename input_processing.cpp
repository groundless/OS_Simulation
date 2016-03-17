//============================================================================
// Name        : input_processing.cpp
// Author      :
// Version     : 0.01
// Description : Basic input program which accepts input from the user in order
//				 to determine the type of processes which will enter the system.
//			     Stores a process_list vector which contains the queue of
//               uninitialized processes, which are net yet in the NEW. The
//               process_list is purely for simulation purposes, and feeds a
//               new process to the OS simulation from process_list.
//============================================================================


/*

Online examples of proper input use
Keeping here temporarily as a guide


void example_inputs() {

 string input = "";

 // How to get a string/sentence with spaces
 cout << "Please enter a valid sentence (with spaces):\n>";
 getline(cin, input);
 cout << "You entered: " << input << endl << endl;

 // How to get a number.
 int myNumber = 0;

 while (true) {
   cout << "Please enter a valid number: ";
   getline(cin, input);

   // This code converts from string to number safely.
   stringstream myStream(input);
   if (myStream >> myNumber)
     break;
   cout << "Invalid number, please try again" << endl;
 }
 cout << "You entered: " << myNumber << endl << endl;

 // How to get a single char.
 char myChar  = {0};

 while (true) {
   cout << "Please enter 1 char: ";
   getline(cin, input);

   if (input.length() == 1) {
     myChar = input[0];
     break;
   }

   cout << "Invalid character, please try again" << endl;
 }
 cout << "You entered: " << myChar << endl << endl;

 cout << "All done. And without using the >> operator" << endl;
}
*/

#include "input_processing.h"
#include <stdlib.h>
#include <time.h>

string input;
int num_processes;
int size_min;
int size_max;
int arrival_min;
int arrival_max;
int runtime_min;
int runtime_max;
int io_min;
int io_max;
std::vector<PCB> process_list;

void begin_input_processing() {

	// Gather all input from the user
	input_total_processes();
	input_process_size();
	input_arrival_interval();
	input_runtime_interval();

	// Build the list from these data
	build_process_list();
}

// Allows us to skip the input processing
void debug_input_processing() {
	num_processes = 60;
	size_min = 1;
	size_max = 8;
	arrival_min = 10;
	arrival_max = 999;
	runtime_min = 1;
	runtime_max = 10;
	io_min = 0;
	io_max = 5;
	build_process_list();
}

void build_process_list () {

	srand(time(NULL));

	int index;
	for (index = 0; index < num_processes; index++) {
		PCB next_process;
		next_process.process_id = rand() % 100;
		next_process.size = rand() % size_max + size_min;
		next_process.total_runtime = rand() % runtime_max + runtime_min;
		next_process.elapsed_runtime = 0;
		process_list.push_back(next_process);
	}

	if (DEBUG) {
		// Display contents of the initial process list
		for (index = 0; index < num_processes; index++) {
			cout << "DEBUG: Process " << (index + 1) << " ID is: " << process_list.at(index).process_id << endl;
			cout << "DEBUG:    - " << "Process" << (index + 1) << " size is: " << process_list.at(index).size << endl;
			cout << "DEBUG:    - " << "Process" << (index + 1) << " runtime is: " << process_list.at(index).total_runtime << endl;
		}
	}
}

/*
 * Takes the next process out of the Process List.
 * The Process List is holding all the processes,
 * and we find a way to simulate their arrival at
 * different times.
 */
PCB retrieve_next_process () {
	PCB next_process;
	next_process.state = "NULL";
	if (process_list.empty()) {
		if (DEBUG){cout << "Process list is empty" << endl;}
		return next_process;
	}
	next_process = process_list.back();
	process_list.pop_back();
	return next_process;
}

void input_total_processes () {
	// Get the number for the total processes, must be between 1-60
	string input = "";
	while (true) {
		cout << "Please enter the total number of processes (between 1 and 60): ";
		getline(cin, input);
		stringstream input_stream(input);
		if (input_stream >> num_processes) {
			if ((num_processes > 60) | (num_processes < 0))
				cout << "The number of processes must be between 1 and 60" << endl;
			else
				break;
		}
		else
			cout << "Invalid number, please try again" << endl;
	}
	cout << "You entered: " << num_processes << endl << endl;
}

void input_process_size () {
	// Get the MIN process size, must be between 1-8
	input = "";
	while (true) {
		cout << "Please enter MINIMUM size for a process (between 1 and 8): ";
		getline(cin, input);
		stringstream input_stream(input);
		if (input_stream >> size_min) {
			if ((size_min > 8) | (size_min < 1))
				cout << "The minimum size of a process must be between 1 and 8" << endl;
			else
				break;
		}
		else
			cout << "Invalid number, please try again" << endl;
	}
	cout << "You entered: " << size_min << endl << endl;

	// Get the MAX process size, must be between 1-8 and greater or equal to MIN size
	input = "";
	while (true) {
		cout << "Please enter MAXIMUM size for a process (between " << size_min << " and 8): ";
		getline(cin, input);
		stringstream input_stream(input);
		if (input_stream >> size_max) {
			if ((size_max > 8) | (size_max < size_min))
				cout << "The minimum size of a process must be between " << size_min << " and 8" << endl;
			else
				break;
		}
		else
			cout << "Invalid number, please try again" << endl;
	}
	cout << "You entered: " << size_max << endl << endl;
}

void input_arrival_interval () {
	// Get the MIN interval for process arrival times
	input = "";
	while (true) {
		cout << "Please enter the MINIMUM range of the arrival time for all the processes: ";
		getline(cin, input);
		stringstream input_stream(input);
		if (input_stream >> arrival_min) {
			if ((arrival_min >= 1000) | (arrival_min < 0))
				cout << "The minimum arrival time range should be between 0 and 999: " << endl;
			else
				break;
		}
		else
			cout << "Invalid number, please try again" << endl;
	}
	cout << "You entered: " << arrival_min << endl << endl;

	// Get the MAX interval for process arrival times
	input = "";
	while (true) {
		cout << "Please enter the MAXIMUM range of the arrival time for all the processes: ";
		getline(cin, input);
		stringstream input_stream(input);
		if (input_stream >> arrival_max) {
			if ((arrival_max >= 1000) | (arrival_max < arrival_min))
				cout << "The maximum arrival time range should be between " << arrival_min << " and 999: " << endl;
			else
				break;
		}
		else
			cout << "Invalid number, please try again" << endl;
	}
	cout << "You entered: " << arrival_max << endl << endl;
}

void input_runtime_interval () {
	// Get the MIN interval for process runtime
	input = "";
	while (true) {
		cout << "Please enter the MINIMUM range of the processing time for all the processes: ";
		getline(cin, input);
		stringstream input_stream(input);
		if (input_stream >> runtime_min) {
			if ((runtime_min > 950) | (runtime_min < 10))
				cout << "The minimum runtime should be between 10 and 950" << endl;
			else
				break;
		}
		else
			cout << "Invalid number, please try again" << endl;
	}
	cout << "You entered: " << runtime_min << endl << endl;

	// Get the MAX interval for process runtime
	input = "";
	while (true) {
		cout << "Please enter the MAXIMUM range of the processing time for all the processes: ";
		getline(cin, input);
		stringstream input_stream(input);
		if (input_stream >> runtime_max) {
			if ((runtime_max > 950) | (runtime_max < runtime_min))
				cout << "The minimum runtime should be between " << runtime_min << " and 950" << endl;
			else
				break;
		}
		else
			cout << "Invalid number, please try again" << endl;
	}
	cout << "You entered: " << runtime_max << endl << endl;
}
