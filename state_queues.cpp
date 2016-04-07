//============================================================================
// Name		   : state_queues.cpp
// Author	   :
// Version	   :
// Description : Main queue declarations
//============================================================================

#include "state_queues.h"

std::vector<PCB> new_queue;
std::vector<PCB> ready_queue;
std::vector<PCB> blocked_queue;
std::vector<PCB> finished_list;
PCB running_process;
