//============================================================================
// Name		   : state_queues.cpp
// Description : Main state queue and main memory definitions.
//               See header file for descriptions.
//============================================================================

#include "state_queues.h"

int main_memory[MEM_SIZE];
std::vector<PCB> new_queue;
std::vector<PCB> ready_queue;
std::vector<PCB> blocked_queue;
std::vector<PCB> finished_list;
PCB running_process;

bool state_changed_flag = false;
string state_changed_description = "";
