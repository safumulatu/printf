#include "main.h"

/************************* WRITE HANDLE *************************/

/**
 * handle_write_char - Prints a character
 * @c: Character to print
 * @buffer: Buffer array to handle printing
 * @flags: Active flags for formatting
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed.
 */
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size)
{
    int i = 0;
    char padd = ' ';

    UNUSED(precision);
    UNUSED(size);

    if (flags & F_ZERO)
        padd = '0';

    buffer[i++] = c;
    buffer[i] = '\0';

    if (width > 1)
    {
        buffer[BUFF_SIZE - 1] = '\0';
        for (i = 0; i < width - 1; i++)
            buffer[BUFF_SIZE - i - 2] = padd;

        if (flags & F_MINUS)
            return (write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
        else
            return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) + write(1, &buffer[0], 1));
    }

    return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/

/**
 * write_number - Writes a number with optional sign and padding
 * @is_negative: Indicates if the number is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Buffer array to handle printing
 * @flags: Active flags for formatting
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
    int length = BUFF_SIZE - ind - 1;
    char padd = ' ', extra_ch = 0;

    UNUSED(size);

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';
    if (is_negative)
        extra_ch = '-';
    else if (flags & F_PLUS)
        extra_ch = '+';
    else if (flags & F_SPACE)
        extra_ch = ' ';

    return write_num(ind, buffer, flags, width, precision, length, padd, extra_ch);
}

/**
 * write_num - Writes a number with optional sign and padding
 * @ind: Index at which the number starts in the buffer
 * @buffer: Buffer array to handle printing
 * @flags: Active flags for formatting
 * @width: Width specifier
 * @length: Length of the number
 * @padd: Character for padding
 * @extra_c: Extra character for sign or space
 *
 * Return: Number of characters printed.
 */
int write_num(int ind, char buffer[], int flags, int width, int length, char padd, char extra_c)
{
    int i, padd_start = 1;

    if (extra_c != 0)
        length++;

    if (width > length)
    {
        for (i = 1; i < width - length + 1; i++)
            buffer[i] = padd;
        buffer[i] = '\0';

        if (flags & F_MINUS && padd == ' ')
        {
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
        }
        else
        {
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
        }
    }

    if (extra_c)
        buffer[--ind] = extra_c;
    return write(1, &buffer[ind], length);
}

/**
 * write_pointer - Writes a memory address
 * @buffer: Buffer array to handle printing
 * @ind: Index at which the number starts in the buffer
 * @length: Length of the number
 * @width: Width specifier
 * @flags: Active flags for formatting
 * @padd: Character for padding
 * @extra_c: Extra character
 * @padd_start: Index at which padding should start
 *
 * Return: Number of characters printed.
 */
int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start)
{
    int i;

    if (width > length)
    {
        for (i = 3; i < width - length + 3; i++)
            buffer[i] = padd;
        buffer[i] = '\0';

        if (flags & F_MINUS && padd == ' ')
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
        }
        else
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
        }
    }
    buffer[--ind] = 'x';
    buffer[--ind] = '0';
    if (extra_c)
        buffer[--ind] = extra_c;
    return write(1, &buffer[ind], BUFF_SIZE - ind - 1);
}
