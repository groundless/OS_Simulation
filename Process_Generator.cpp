//============================================================================
// Name        : Process_Generator.cpp
// Author      : Chris Lucas
// Version     : 0.1
// Copyright   :
// Description : Generates processes to be simulated in the OS simulation
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RUN_MAX 950
#define RUN_MIN 10
#define IO_MAX 5
#define SIZE_MAX 8
#define SIZE_MIN 1

using namespace std;

int main() {
	ofstream simFile;
	char choice;
	bool correct;
	int numProcesses, input;

	srand(time(NULL));
	
	// Creates/Overwrites the Processes.txt file
	
	simFile.open("Processes.txt");

	// Asks the user how many processes they would like to generate.
	// If the input is not within the proper bounds, the code returns an error and asks for a new input.

	do{
		cout << "How many processes would you like to generate? (10 to 60):";
		cin >> numProcesses;
		if(numProcesses < 10 || numProcesses > 60){
			cout << "ERROR: Input not within bounds." << endl;
		}
	}while(numProcesses < 10 || numProcesses > 60);

	// Provides the user the choice between automatic and manual generation of processes

	cout << "Would you like to manually or automatically generate the processes? (m or a): ";
	cin >> choice;

	// Checks if the input is of the correct format and then executes based on the choice made
	// If the input is not in the correct format, the code returns an error and asks again.

	while (!correct){
		
		// Code for automatic generation of the processes
		
		if (choice == 'a' || choice == 'A'){
			for(int i = 0; i < numProcesses; i++){
				simFile << rand() % (RUN_MAX - RUN_MIN +1) + RUN_MIN << "\t\t";  //total runtime
				simFile << rand() % (IO_MAX+1) << "\t";  //number of IO requests
				simFile << rand() % SIZE_MAX + SIZE_MIN;  //size of process in MB
				if(i != (numProcesses - 1)){
					simFile << endl;  //ensures that there isn't an extra line at the end of the file
				}
			}
			correct = true;
		}else if(choice == 'm'|| choice == 'M'){
			
			// code for manual generation of the processes
			// this method is not suggested as it can be consuming of the user's time

			cout << "Processes can also be manually changed within the Proccesses.txt file once generated." << endl;
			for(int i = 0; i < numProcesses; i++){
				
				// Asks the user for the total runtime for the process
				// Checks if the value is within the proper bounds

				do {
					cout << "Please input the total run time of process "<< i << " (10 to 950): ";
					cin >> input;
					if (input < 10 || input > 950){
						cout << "ERROR: Input not within bounds." << endl;
					}
				} while (input < 10 || input > 950);
				simFile << input << "\t\t";  //total runtime
				
				// Asks the user for the number of IO requests for the process
				// Checks if the value is within the proper bounds

				do {
					cout << "Please input the number of IO requests for process "<< i << " (0 to 5): ";
					cin >> input;
					if (input < 0 || input > 5){
						cout << "ERROR: Input not within bounds." << endl;
					}
				} while (input < 0 || input > 5);
				simFile << input << "\t";  //number of IO requests
				
				// Asks the user for the size in memory that the process takes up
				// Checks if the value is within the proper bounds

				do {
					cout << "Please input the size of process "<< i << " (1 to 8 MB): ";
					cin >> input;
					if (input < 1 || input > 8){
						cout << "ERROR: Input not within bounds." << endl;
					}
				} while (input < 1 || input > 8);
				simFile << input;  //size of process in MB
				if(i != (numProcesses - 1)){
					simFile << endl;  //ensures that there isn't an extra line at the end of the file
				}
				
				// Clears screen so that the display only shows the values for the current process

				system("cls");
			}
			correct = true;
		}
		if (!correct){
			cout << "Error, please input whether you would like to manually or automatically generate the processes? (m or a): ";
			cin >> choice;
		}
	}
	cout << "Process_Generator.exe will now exit." << endl;
	simFile.close();
	return 0;
}
