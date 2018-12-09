/* terminal.c - Functions to interact with the terminal
 * vim:ts=4 noexpandtab
 */

#include "keyboard.h"
#include "lib.h"

/*terminal_open
 *Description: Open the terminal
 *Inputs:      none
 *Outputs:     Return 0-Success
 *                    1-Failure
 *Effects:     Set the frequency of rtc to 2HZ
 */
int32_t terminal_open(void) {
    read_flag = READ_DISABLE;
    return 0;
}

/*terminal_close
 *Description: close terminal
 *Inputs:      buf- hold the value of frequency to be set
 *             nbytes- need to be 4 to work
 *Outputs:     none
 *Effects:     Set RTC frequency to the value in buf
 */
int32_t terminal_close(int32_t fd) {
    return 0;
}

/*terminal_read
 *Description: Read the keyboard input buffer
 *Inputs:      buf- whatever
 *             nbytes- whatever
 *Outputs:     Return 0-Success
 *                    1-Failure
 *Effects:     Read after interrupt occur and reset the flag
 */
int32_t terminal_read(int32_t fd, void* buf, int32_t nbytes) {

    int end_position;
    buf = (unsigned char*)buf;
    while (!read_flag) {}

    /* if there has been a line in the input buffer currently */
    if (new_lines_location > 0) {
        end_position = new_lines[0];
        /* if the line is shoter than the output buffer size, we copy the entire line */
        if (nbytes > end_position) {
            memcpy(buf, input_buffer, end_position);
            ((unsigned char*)buf)[end_position] = '\n';
            input_location -= end_position;
            memmove(input_buffer, input_buffer + end_position, input_location);
            new_lines_location--;
            memmove(new_lines, new_lines + 1, new_lines_location);
            read_flag = READ_DISABLE;
            return end_position + 1;
        }
        /* if the line is longer than the output buffer size, we align it into the buffer */
        else {
            memcpy(buf, input_buffer, nbytes-1);
            ((unsigned char*)buf)[nbytes-1] = '\0';
            input_location -= end_position;
            memmove(input_buffer, input_buffer + end_position, input_location);
            new_lines_location--;
            memmove(new_lines, new_lines + 1, new_lines_location);
            read_flag = READ_DISABLE;
            return nbytes;
        }
    }
    /* there has not been a existing line yet */
    else {
        read_flag = READ_DISABLE;
        return 0;
    }
}

/*terminal_write
 *Description: output the buffer input
 *Inputs:      buf- hold the value of frequency to be set
 *             nbytes- need to be 4 to work
 *Outputs:     none
 *Effects:     Set RTC frequency to the value in buf
 */
int32_t terminal_write(int32_t fd, const uint8_t* buf, int32_t nbytes) {
    int32_t i = 0;
    for (i = 0; i < nbytes; i++) {
        putc(buf[i]);
    }
    return i;
}
