//============================================================================
// Name        : process_arrival.cpp
// Description : functions pertaining to simulated arrival of processes
//============================================================================

#include "process_arrival.h"

PCB retrieve_next_process (ifstream& inputFile) {
	int runtime = 0, IO = 0, size = 0, IO_min = 0, elapsedTime = 0;
	static int cycleCount = 0, arrival = 0, PID = 0;
	static bool empty_list = false;
	string state = "NEW";
	if(!empty_list){
		if (arrival == 0){
			arrival = rand() % (475-5+1)+5;
			cycleCount++;
		}else if(cycleCount == arrival){
			arrival = 0;
			cycleCount = 0;
			if (!inputFile.eof()) {
				PID++;
				inputFile >> runtime >> IO >> size;
				PCB next_process(PID, state, runtime, elapsedTime, IO, IO_min, size);
				return next_process;
			}else{
				if (DEBUG){cout << "Process list is empty" << endl;}
				empty_list = true;
			}
		}else{
			cycleCount++;
		}
	}
	PCB next_process;
	next_process.set_state("NULL");
	return next_process;
}

void check_file(ifstream& inputFile){
	string line; int line_piece;
	int runtime, io, size, on_line, count = 0;
	std::vector<int> check_duplicates;
	while(!inputFile.eof()){
		on_line = 0;
		getline(inputFile,line);
		istringstream seperate(line);
		while(seperate >> line_piece){
			on_line++;
			switch(on_line){
				case 1:
					runtime = line_piece;
					if(runtime > 950 || runtime < 10){
						cout << "ERROR: Process on line " << count+1 << "has an incorrect runtime value. Please make sure that the Processes.txt file follows the correct format and try again." << endl;
						exit(0);
					}
					break;
				case 2:
					io = line_piece;
					if(io > 5 || runtime < 0){
						cout << "ERROR: Process on line " << count+1 << "has an incorrect IO value. Please make sure that the Processes.txt file follows the correct format and try again." << endl;
						exit(0);
					}
					break;
				case 3:
					size = line_piece;
					if(size > 8 || runtime < 1){
						cout << "ERROR: Process on line " << count+1 << "has an incorrect size value. Please make sure that the Processes.txt file follows the correct format and try again." << endl;
						exit(0);
					}
					break;
				default :
					cout << "ERROR: Too many entries on line " << count+1 << ". Please make sure that the Processes.txt file follows the correct format and try again." << endl;
					exit(0);
					break;
			}
		}
		count++;
		if(on_line < 3){
			cout << "ERROR: Too few entries on line " << count << ". Please make sure that the Processes.txt file follows the correct format and try again." << endl;
			exit(0);
		}
	}
	inputFile.clear();
	inputFile.seekg(0, inputFile.beg);
	if(count < 10){
		cout << "ERROR: too few processes in Processes.txt. Please make sure there are at least 10 processes in the file." << endl;
		exit(0);
	}else if(count > 60){
		cout << "ERROR: too many processes in Processes.txt. Please make sure there are no more than 60 processes in the file." << endl;
		exit(0);
	}

}

