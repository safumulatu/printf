#ifndef MAIN_H
#define MAIN_H

/* Include necessary standard libraries */
#include <stdarg.h>  // For variable argument lists
#include <stdio.h>   // For standard I/O functions
#include <unistd.h>  // For POSIX operating system API

#define UNUSED(x) (void)(x) // A macro to silence unused variable warnings
#define BUFF_SIZE 1024      // Define a buffer size constant

/* FLAGS: These constants represent various format flags */
#define F_MINUS 1	// Flag for left-justify
#define F_PLUS 2	// Flag for including a '+' sign for positive numbers
#define F_ZERO 4	// Flag for zero-padding
#define F_HASH 8	// Flag for alternative form (used with o, x, X specifiers)
#define F_SPACE 16	// Flag for including a space for positive numbers

/* SIZES: These constants represent size modifiers */
#define S_LONG 2	// 'l' modifier (long int or double)
#define S_SHORT 1	// 'h' modifier (short int)

/**
 * struct fmt - Structure for format specifiers
 *
 * @fmt: The format character.
 * @fn: The function associated with the format character.
 */
struct fmt {
	char fmt;				// The format character
	int (*fn)(va_list, char[], int, int, int, int); // Function pointer for handling the format
};

/**
 * typedef struct fmt fmt_t - Typedef for struct fmt
 *
 * @fmt: The format character.
 * @fn: The function associated with the format character.
 */
typedef struct fmt fmt_t;

/* Function prototypes for the _printf function and related functions */
int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i, va_list list, char buffer[], int flags, int width, int precision, int size);

/* Functions for printing characters and strings */
int print_char(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Functions for printing numbers in various formats */
int print_int(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Function to print hexadecimal values */
int print_hexa(va_list types, char map_to[], char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Function to print non-printable characters */
int print_non_printable(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Function to print memory addresses */
int print_pointer(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Functions to handle other format specifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/* Function to print a string in reverse */
int print_reverse(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Function to print a string in ROT13 encoding */
int print_rot13string(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Functions for handling width and formatting */
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[], int flags, int width, int precision, int size);
int write_num(int ind, char bff[], int flags, int width, int precision, int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start);
int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size);

/* Utility functions */
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */

