//============================================================================
// Name		   : output_ui.cpp
// Description : User Interface functions.
//============================================================================

#include "output_ui.h"

// Flag which indicates whether we are allowing the OS
// to run to completion, i.e. slowly display the state
// changes of the processes as the OS functions.
bool run_to_completion = false;

// Step indicates the number of seconds to sleep between
// states updating. User specified.
int step = 0;

// The primary control function called after every major
// function call to the operating system. This function lets
// the user run to completion or continue to monitor the state
// changes. Holds and waits for user input.
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

void display_memory () {

    cout << "Main Memory" << endl;
	cout << endl;

    //Adjusts spacing for indexes with 1 vs 2 numbers (eg. 7 vs 12)
	for(int i = 0; i < 16; i++){

        if((i+1) < 10){
            cout <<"  "<< (i+1)<<"  ";
        }
        else{
            cout <<" " <<(i+1)<<"  ";
        }
	}

    cout << endl << "--------------------------------------------------------------------------------" << endl;

	//Print process IDs in memory in a linear square format. Single digit numbers are preceded by a '0'
	for(int i = 0; i < 16; i++){

        if(main_memory[i] < 10){
            cout << " " << "0" << main_memory[i] << " |";
        }
        else {
            cout << " " << main_memory[i] << " |";
        }
	}

    cout << endl << "--------------------------------------------------------------------------------" << endl << endl;
}


// From the Project Specifications:
// For each active process the following information should be displayed:
// amount of CPU time needed to complete, amount of CPU time already used,
// priority (if relevant), number of I/O requests satisfied,
// number of outstanding I/O requests.

void display_ui () {

	unsigned int index;
	//Clear the screen
	clear_console();

	
	 /*
     * Following code prints out all the queues and the process ID's within them
     */
	cout << "New Queue size: " << new_queue.size() << endl;
	cout << "------------------" << endl;
	cout << "->";
	for (index = 0; index < new_queue.size(); index++) {
		cout << "[" << new_queue.at(index).get_id() << "]"<<" ";
	}

	cout << endl << endl;

	cout << "Ready Queue size: " << ready_queue.size() << endl;
	cout << "--------------------" << endl;
	cout << "->";
	for (index = 0; index < ready_queue.size(); index++) {
		cout << "[" << ready_queue.at(index).get_id() << "]"<<" ";
	}

	cout << endl << endl;
	//Shows IDs of processes loaded into memory.
    display_memory();

    cout << "Running process: " << endl
		<< "-----------------" << endl;
    cout << "->";//Arrow to show the head of the queue
	if (!running_process.check_state("NULL")) {//Checking if there is a process in the running queue

        cout
        << "ID: " << running_process.get_id() <<" "<< endl
        << "  CPU time needed to complete: " << running_process.runtime_remaining() << endl
        << "  CPU time already used: " << running_process.get_elapsed_runtime() << endl
        << "  IO requests fulfilled: " << running_process.get_io_completed() << "/" <<running_process.iorequests_remaining() + running_process.get_io_completed() << endl;

	}
	else {
        cout << "No process running" << endl;
	}

    cout << endl << endl;

	cout << "Blocked Queue size: " << blocked_queue.size() << endl;
	cout << "---------------------" << endl;
	cout << "->";
	for (index = 0; index < blocked_queue.size(); index++) {
		cout << "[" << blocked_queue.at(index).get_id() << "]"<<" ";
	}

	cout << endl << endl;

	cout << "Exiting Process " << endl;
	cout << "---------------" << endl;
	if (!finished_list.empty()) {
		cout << "[" << finished_list.front().get_id() << "]";
		finished_list.erase(finished_list.begin());
	}

	cout << endl << endl << endl;
	
    //Output which process (ID) changed state and the state change itself. Set by functions which cause state changes
	cout << state_changed_description << endl << endl;
}

/*
 * Debugging function, prints out the processes in the state queues.
 */
void debug_print () {

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

		if (!running_process.check_state("NULL")) {
			cout << "DEBUG: Running process: " << running_process.get_id() << " CPU time needed to complete: " << running_process.get_elapsed_runtime() << endl;
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
 * Debugging function, prints out the memory in list.
 */
void debug_print_memory() {
	if (DEBUG) {
		cout << "Main Memory" << endl;
		cout << "----------------------------" << endl;
		for (int i = 0; i < 4; i++) {
			//cout << "Main Memory " << i << ": PID " << main_memory[i] << endl;
			cout << (i+1)    << ": " << main_memory[i] << "\t";
			cout << (i+4)+1  << ": " << main_memory[i+4] << "\t";
			cout << (i+8)+1  << ": " << main_memory[i+8] << "\t";
			cout << (i+12)+1 << ": " << main_memory[i+12] << endl;
		}
		cout << "----------------------------" << endl;
	}
}

void move_cursor (short x, short y) {
	 COORD coord = {x, y};
	 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clear_console() {
	system("cls");
	/*
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {0, 0};
	DWORD count;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
		SetConsoleCursorPosition(hStdOut, coord);
	}
	*/
}

void initialize_console () {
	int width = 100;
	int height = 50;

    _COORD coord;
    coord.X = width;
    coord.Y = height;

    _SMALL_RECT new_window;
    new_window.Top = 0;
    new_window.Left = 0;
    new_window.Bottom = height - 1;
    new_window.Right = width - 1;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(handle, coord);
    SetConsoleWindowInfo(handle, TRUE, &new_window);

    /*
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL){
    	MoveWindow(hwnd, 200, 200, 800, 800, TRUE);
    }
    */
}
