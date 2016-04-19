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
	simFile.open("Processes.txt");

	cout << "How many processes would you like to generate? (1 to 60):";
	cin >> numProcesses;
	cout << "Would you like to manually or automatically generate the processes? (m or a): ";
	cin >> choice;

	while (!correct){
		if (choice == 'a' || choice == 'A'){
			for(int i = 0; i < numProcesses; i++){
				simFile << i << " ";												//process id
				simFile << rand() % (RUN_MAX - RUN_MIN +1) + RUN_MIN << " ";		//total runtime
				simFile << rand() % (IO_MAX+1) << " ";								//number of IO requests
				simFile << rand() % SIZE_MAX + SIZE_MIN << endl;					//size of process in MB
			}
			correct = true;
		}else if(choice == 'm'|| choice == 'M'){
			cout << "Processes can also be manually changed within the Proccesses.txt file once generated." << endl;
			for(int i = 0; i < numProcesses; i++){
				simFile << i << " ";												//process id
				do {
					cout << "Please input the total run time of process "<< i << " (10 to 950): ";
					cin >> input;
					if (input < 10 || input > 950){
						cout << "ERROR: Input not within bounds." << endl;
					}
				} while (input < 10 || input > 950);
				simFile << input << " ";											//total runtime
				do {
					cout << "Please input the number of IO requests for process "<< i << " (0 to 5): ";
					cin >> input;
					if (input < 0 || input > 5){
						cout << "ERROR: Input not within bounds." << endl;
					}
				} while (input < 0 || input > 5);
				simFile << input << " ";											//number of IO requests
				do {
					cout << "Please input the size of process "<< i << " (1 to 8 MB): ";
					cin >> input;
					if (input < 1 || input > 8){
						cout << "ERROR: Input not within bounds." << endl;
					}
				} while (input < 1 || input > 8);
				simFile << input << endl;											//size of process in MB
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
