#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Size specifier.
 */
int get_size(const char *format, int *i)
{
    int curr_i = *i + 1;
    int size = 0;

    if (format[curr_i] == 'l') {
        size = S_LONG;
        if (format[curr_i + 1] == 'l') {
            size = S_LONG_LONG;
            curr_i++;  // Skip the second 'l'
        }
    } else if (format[curr_i] == 'h') {
        size = S_SHORT;
        if (format[curr_i + 1] == 'h') {
            size = S_CHAR;
            curr_i++;  // Skip the second 'h'
        }
    }

    if (size == 0)
        *i = curr_i - 1;
    else
        *i = curr_i;

    return size;
}
