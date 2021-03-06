//============================================================================
// Name		   : state_queues.cpp
// Author	   :
// Version	   :
// Description : Main queue declarations
//============================================================================

#include "state_queues.h"

int main_memory[MEM_SIZE];
std::vector<PCB> new_queue;
std::vector<PCB> ready_queue;
std::vector<PCB> blocked_queue;
std::vector<PCB> finished_list;
PCB running_process;
bool state_changed_flag = false;
