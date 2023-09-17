#include "main.h"
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

/**
 * print_pointer - Print a pointer in hexadecimal format
 * @args: The va_list containing the pointer argument
 * @chars_printed: A pointer to the total characters printed
 */
void print_pointer(va_list args, int *chars_printed)
{
	void *ptr = va_arg(args, void *);

	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		*chars_printed += 5;
		return;
	}

	/* Convert the pointer value to hexadecimal string */
	unsigned long int value = (unsigned long int)ptr;
	char hex_buffer[16]; /* Adjust the size as needed */
	int i = 0;

	while (value > 0)
	{
		int remainder = value % 16;

		hex_buffer[i++] = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
		value /= 16;
	}

	/* Print the hexadecimal string in reverse order */
	for (i--; i >= 0; i--)
	{
		write(1, &hex_buffer[i], 1);
		(*chars_printed)++;
	}
}

/**
 * _printf - Custom printf function
 * @format: The format string
 * @...: The variable number of arguments
 *
 * Return: The number of characters printed (excluding the null terminator)
 */
int _printf(const char *format, ...)
{
	if (format == NULL)
		return (-1);

	va_list args;
	int chars_printed = 0;

	va_start(args, format);

	while (*format)
	{
		if (*format != '%')
		{
			write(1, format, 1);
			chars_printed++;
		}
		else
		{
			format++;
			if (*format == 'p')
			{
				void *ptr = va_arg(args, void *);

				if (ptr == NULL)
				{
					write(1, "(nil)", 5);
					chars_printed += 5;
				}
				else
				{
					print_pointer(args, &chars_printed);
				}
			}
			/* Add more cases for other conversion specifiers if needed */
		}
		format++;
	}

	va_end(args);

	return (chars_printed);
}

/* Additional helper functions and cases for other specifiers can be added */

int main(void)
{
	void *ptr = (void *)0x12345678;

	_printf("Pointer address: %p\n", ptr);

	return (0);
}
