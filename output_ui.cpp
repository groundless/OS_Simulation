//============================================================================
// Name		   : interrupts.cpp
// Author	   :
// Version	   :
// Description : Function declarations for the IO
//============================================================================

#include "output_ui.h"
#include "Windows.h"
#include "Wincon.h"

/*
 * Windows definition specific to the console functions, see the following:
 * https://msdn.microsoft.com/en-us/library/windows/desktop/aa383745(v=vs.85).aspx
 */
#define _WIN32_WINNT 0x0502
/*
 * Print out the main_memory array visually.
 * For debugging purposes.
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

/*
 * Debugging function, prints out the processes in the NEW and READY queue.
 */
void debug_print () {

	debug_print_memory();

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
