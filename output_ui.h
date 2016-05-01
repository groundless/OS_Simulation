//============================================================================
// Name		   : output_ui.h
// Author	   :
// Version	   :
// Description : Function definitions for the output
//============================================================================

#ifndef OUTPUT_UI_H_
#define OUTPUT_UI_H_


#include "state_queues.h"
#include "windows.h"
#include "wincon.h"

/*
 * Windows definition specific to the console functions, see the following:
 * https://msdn.microsoft.com/en-us/library/windows/desktop/aa383745(v=vs.85).aspx
 * NOTE: Be careful with redefining this value, it may be necessary to redefine this
 * for some newer versions of Windows.
 */
//#define _WIN32_WINNT 0x0502

void hold_on_state_change();
void display_ui();
void clear_console();
void initialize_console();
void debug_print();

#endif /* OUTPUT_UI_H_ */
