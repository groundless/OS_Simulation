/*
 * process_arrival.h
 *
 *  Created on: May 1, 2016
 *      Author: Aceco_000
 */

#ifndef PROCESS_ARRIVAL_H_
#define PROCESS_ARRIVAL_H_

#include "state_queues.h"

PCB retrieve_next_process (ifstream& inputFile);
void check_file(ifstream& inputFile);

#endif /* PROCESS_ARRIVAL_H_ */
