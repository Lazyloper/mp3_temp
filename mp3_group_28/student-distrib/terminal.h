/* terminal.h - Defines used in interactions with the terminal
 * vim:ts=4 noexpandtab
 */
#ifndef _TERMINAL_H
#define _TERMINAL_H

#include "types.h"

/* Externally-visible functions */

int32_t terminal_open(const uint8_t* filename);

int32_t terminal_close(int32_t fd);

int32_t terminal_read(int32_t fd, void* buf, int32_t nbytes);

int32_t terminal_write(int32_t fd, const void* buf, int32_t nbytes);

#endif
