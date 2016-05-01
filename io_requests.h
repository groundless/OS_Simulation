//============================================================================
// Name		   : io_requests.h
// Description : Functions related to the processing of IO requests.
//============================================================================

#ifndef IO_REQUESTS_H_
#define IO_REQUESTS_H_

#include "state_queues.h"

void check_io_interrupt();
void process_io_devices();

#endif /* IO_REQUESTS_H_ */
