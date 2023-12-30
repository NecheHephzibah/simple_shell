#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include "main.h"

void _fputchar(char c);
int _power(int base, int exponent);
unsigned long int str_to_num(char *s);
int _print_num(long int, int);
int _print_bin(unsigned int num, int count);
int _print_unsigned_num(unsigned long int num);
int _print_octal(unsigned long int num);
int _print_hex(unsigned long int num, int flag);
int is_flag(char c);
int is_format(char c);
int padding(int pad_width);
int zero_padding(int pad_width);
int len(char *str);
int _print_num_count(long int);
int _print_unsigned_num_count(unsigned long int num);
int _print_octal_count(unsigned long int num);
int _print_hex_count(unsigned long int num, int flag);

/**
 * _printf - prints formatted arguments passed
 * @format: pointer to format specifiers
 * Return: If Success- number of characters printed to stdout otherwise -1
 */
int _fprintf(const char *format, ...)
{
	va_list ap;
	int i = 0, j, k, l, no_lh = 0, t = 0, min_width_size, foo, bar, flag_star = 0;
	int count = 0, flag_index = 0, flag_plus = 0, flag_space = 0, flag_hash = 0;
	long int num;
	unsigned long int num2;
	int percent_space = 0, flag_ell = 0, flag_h = 0, flag_width = 0, flag_neg = 0;
	int m, n, m0, m1, flag_precision = 0, min_precision = 0, flag_star_p = 0, q;
	int zpad = 0, x = 0, y = 0, z = 0, p = 0, pre = 0, flag_zero = 0, str_len = 0;
	char *string, *temp_string, *width, *precision;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	while (format && format[i])
	{
		if (format[i] != '%')
			_fputchar(format[i]), count++;
		if (format[i] == '%')
		{
		i++;
		if (format[i] == '\0')
			return (-1);
		while (is_flag(format[i]))
		{
			if (flag_index == 0)
				j = i;
			flag_index++;
			if (format[i] == '+')
				flag_plus = 1;
			if (format[i] == ' ')
				flag_space = 1;
			if (format[i] == '#')
				flag_hash = 1;
			if (format[i] == '0')
				flag_zero = 1;
			if (format[i] == '-')
				flag_neg = 1;
			i++;
		}
		k = i;
		while ((format[i] >= '1' && format[i] <= '9') || (format[i] == '*'))
		{
			if (format[i] == '*')
				flag_star = 1;
			i++;
		}
		l = i;
		i = k;
		if (l > k)
		{
			flag_width = 1;
			if (flag_star == 1)
			{
				min_width_size = va_arg(ap, int);
				i++;
			}
			else
			{
				width = malloc((l - k + 1) * sizeof(char));
				if (width == NULL)
					return (-1);
				while (format[i] >= '1' && format[i] <= '9')
				{
					width[t++] = format[i];
					i++;
				}
				width[t] = '\0';
				min_width_size = str_to_num(width);
			}
		}
		m = i;
		if (format[i] == '.')
		{
			flag_precision = 1;
			i++;
			m0 = i;
			while ((format[i] >= '0' && format[i] <= '9') || (format[i] == '*'))
			{
				if (format[i] == '*')
					flag_star_p = 1;
				i++;
			}
			m1 = i;
			i = m0;
			if (m1 > m0)
			{
				if (flag_star_p == 1)
				{
					min_precision = va_arg(ap, int);
					i++;
				}
				else
				{
					precision = malloc((m1 - m0 + 1) * sizeof(char));
					if (precision == NULL)
						return (-1);
					while (format[i] >= '0' && format[i] <= '9')
					{
						precision[p++] = format[i];
						i++;
					}
					precision[p] = '\0';
					min_precision = str_to_num(precision);
				}
			}
		}
		n = i;
		if (format[i] == 'l' || format[i] == 'h')
		{
			if (is_format(format[i + 1]))
			{
				if (format[i] == 'l')
					flag_ell = 1;
				if (format[i] == 'h')
					flag_h = 1;
				i++;
			}
			else
			{
				no_lh = 1;
			}
		}
		if (flag_width == 1 && !(is_format(format[i])))
		{
			i -= l - k;
			if (flag_star != 1)
				free(width);
			flag_width = flag_star = 0;
		}
		if (flag_precision == 1 && !(is_format(format[i])))
		{
			i -= n - m;
			if (flag_star_p != 1)
				free(precision);
			flag_precision = flag_star_p = 0;
		}
		if ((flag_index != 0) && !(is_format(format[i])))
		{
			i = j;
			flag_plus = flag_space = flag_hash = flag_zero = flag_neg = 0;
		}
		flag_index = 0;
		switch (format[i])
		{
		case 'c':
			if ((flag_width == 1) && (min_width_size > 1) && (flag_neg == 0))
				count += padding(min_width_size - 1);
			_fputchar(va_arg(ap, int)), count++;
			if ((flag_width == 1) && (min_width_size > 1) && (flag_neg == 1))
				count += padding(min_width_size - 1);
			break;
		case 's':
			string = va_arg(ap, char*);
			if (string == NULL)
				string = "(null)";
			if (flag_precision == 1)
				foo = min_precision;
			else
				foo = len(string);
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
				count += padding(min_width_size - foo);
			if (flag_precision == 1 && min_precision == 0)
				break;
			while (*string)
			{
				_fputchar(*string++), count++;
				if (flag_precision == 1)
				{
					pre++;
					if (pre >= min_precision)
						break;
				}
			}
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 1))
				count += padding(min_width_size - foo);
			pre = 0;
			break;
		case '%':
			if ((flag_width == 1) && (min_width_size > 1) && (flag_neg == 0))
				count += padding(min_width_size - 1);
			_fputchar('%'), count++;
			if ((flag_width == 1) && (min_width_size > 1) && (flag_neg == 1))
				count += padding(min_width_size - 1);
			break;
		case 'd':
			if (flag_ell == 1)
				num = va_arg(ap, long int);
			else
				num = va_arg(ap, int);
			if (flag_precision == 1)
			{
				bar = _print_num_count(num) - (num < 0);
				if (bar < min_precision)
				{
					z = min_precision - bar;
					y = z - (num < 0);
				}
			}
			if (flag_width == 1)
				foo = _print_num_count(num) + ((flag_plus || flag_space) * (num >= 0)) + y;
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
			{
				if (!(flag_zero == 1 && flag_precision == 0))
				{
					count += padding(min_width_size - foo);
					if (num == 0 && flag_precision == 1 && min_precision == 0)
						count += padding(1);
				}
			}
			if (flag_plus == 1 && num >= 0)
				_fputchar('+'), count++;
			if (flag_space == 1 && num >= 0 && flag_plus == 0)
				_fputchar(' '), count++;
			if (!(num == 0 && flag_precision == 1 && min_precision == 0))
			{
				if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
				{
					if (flag_zero == 1 && flag_precision == 0)
						x = min_width_size - foo;
				}
				count += _print_num(num, z + x);
			}
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 1))
			{
				count += padding(min_width_size - foo);
				if (num == 0 && flag_precision == 1 && min_precision == 0)
					count += padding(1);
			}
			break;
		case 'i':
			if (flag_ell == 1)
				num = va_arg(ap, long int);
			else
				num = va_arg(ap, int);
			if (flag_precision == 1)
			{
				bar = _print_num_count(num) - (num < 0);
				if (bar < min_precision)
				{
					z = min_precision - bar;
					y = z - (num < 0);
				}
			}
			if (flag_width == 1)
				foo = _print_num_count(num) + ((flag_plus || flag_space) * (num >= 0)) + y;
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
			{
				if (!(flag_zero == 1 && flag_precision == 0))
				{
					count += padding(min_width_size - foo);
					if (num == 0 && flag_precision == 1 && min_precision == 0)
						count += padding(1);
				}
			}
			if (flag_plus == 1 && num >= 0)
				_fputchar('+'), count++;
			if (flag_space == 1 && num >= 0 && flag_plus == 0)
				_fputchar(' '), count++;
			if (!(num == 0 && flag_precision == 1 && min_precision == 0))
			{
				if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
				{
					if (flag_zero == 1 && flag_precision == 0)
						x = min_width_size - foo;
				}
				count += _print_num(num, z + x);
			}
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 1))
			{
				count += padding(min_width_size - foo);
				if (num == 0 && flag_precision == 1 && min_precision == 0)
					count += padding(1);
			}
			break;
		case 'b':
			count = _print_bin(va_arg(ap, unsigned int), count);
			break;
		case 'u':
			if (flag_ell == 1)
				num2 = va_arg(ap, unsigned long int);
			else if (flag_h == 1)
				num2 = va_arg(ap, int);
			else
				num2 = va_arg(ap, unsigned int);
			if (flag_precision == 1)
			{
				bar = _print_unsigned_num_count(num2);
				if (bar < min_precision)
					zpad = min_precision - bar;
			}
			if (flag_width == 1)
				foo = _print_unsigned_num_count(num2) + zpad;
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
			{
				if (flag_zero == 1 && flag_precision == 0)
					count += zero_padding(min_width_size - foo);
				else
					count += padding(min_width_size - foo);
			}
			if ((flag_precision == 1) && (bar < min_precision))
				count += zero_padding(zpad);
			if (num2 == 0 && flag_precision == 1 && min_precision == 0)
				break;
			count += _print_unsigned_num(num2);
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 1))
				count += padding(min_width_size - foo);
			break;
		case 'o':
			if (flag_ell == 1)
				num2 = va_arg(ap, unsigned long int);
			else if (flag_h == 1)
				num2 = va_arg(ap, int);
			else
				num2 = va_arg(ap, unsigned int);
			if (flag_precision == 1)
			{
				bar = _print_octal_count(num2);
				if (bar < min_precision)
					zpad = min_precision - bar;
			}
			if (flag_width == 1)
				foo = _print_octal_count(num2) + (flag_hash * (num2 != 0)) + zpad;
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
			{
				if (!(flag_zero == 1 && flag_precision == 0))
					count += padding(min_width_size - foo);
			}
			if (flag_hash == 1 && num2 != 0)
				_fputchar('0'), count++;
			if ((flag_precision == 1) && (bar < min_precision))
				count += zero_padding(zpad);
			if (num2 == 0 && flag_precision == 1 && min_precision == 0)
				break;
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
			{
				if (flag_zero == 1 && flag_precision == 0)
					count += zero_padding(min_width_size - foo);
			}
			count += _print_octal(num2);
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 1))
				count += padding(min_width_size - foo);
			break;
		case 'x':
			if (flag_ell == 1)
				num2 = va_arg(ap, unsigned long int);
			else if (flag_h == 1)
				num2 = va_arg(ap, int);
			else
				num2 = va_arg(ap, unsigned int);
			if (flag_precision == 1)
			{
				bar = _print_hex_count(num2, 0);
				if (bar < min_precision)
					zpad = min_precision - bar;
			}
			if (flag_width == 1)
				foo = _print_hex_count(num2, 0) + ((flag_hash * (num2 != 0)) * 2) + zpad;
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
			{
				if (!(flag_zero == 1 && flag_precision == 0))
					count += padding(min_width_size - foo);
			}
			if (flag_hash == 1 && num2 != 0)
			{
				_fputchar('0'), count++;
				_fputchar('x'), count++;
			}
			if ((flag_precision == 1) && (bar < min_precision))
				count += zero_padding(zpad);
			if (num2 == 0 && flag_precision == 1 && min_precision == 0)
				break;
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
			{
				if (flag_zero == 1 && flag_precision == 0)
					count += zero_padding(min_width_size - foo);
			}
			count += _print_hex(num2, 0);
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 1))
				count += padding(min_width_size - foo);
			break;
		case 'X':
			if (flag_ell == 1)
				num2 = va_arg(ap, unsigned long int);
			else if (flag_h == 1)
				num2 = va_arg(ap, int);
			else
				num2 = va_arg(ap, unsigned int);
			if (flag_precision == 1)
			{
				bar = _print_hex_count(num2, 1);
				if (bar < min_precision)
					zpad = min_precision - bar;
			}
			if (flag_width == 1)
				foo = _print_hex_count(num2, 1) + ((flag_hash * (num2 != 0)) * 2) + zpad;
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
			{
				if (!(flag_zero == 1 && flag_precision == 0))
					count += padding(min_width_size - foo);
			}
			if (flag_hash == 1 && num2 != 0)
			{
				_fputchar('0'), count++;
				_fputchar('X'), count++;
			}
			if ((flag_precision == 1) && (bar < min_precision))
				count += zero_padding(zpad);
			if (num2 == 0 && flag_precision == 1 && min_precision == 0)
				break;
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
			{
				if (flag_zero == 1 && flag_precision == 0)
					count += zero_padding(min_width_size - foo);
			}
			count += _print_hex(num2, 1);
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 1))
				count += padding(min_width_size - foo);
			break;
		case 'S':
			string = va_arg(ap, char*);
			if (string == NULL)
				string = "(null)";
			while (*string)
			{
				if (((*string > 0) && (*string < 32)) || (*string >= 127))
				{
					if (*string < 16)
						count += _fprintf("\\x0%X", *string++);
					else
						count += _fprintf("\\x%X", *string++);
				}
				else
				{
					_fputchar(*string++), count++;
				}
			}
			break;
		case 'p':
			string = va_arg(ap, void*);
			if (string == NULL)
			{
				string = "(nil)";
				if ((flag_width == 1) && (len(string) < min_width_size) && (flag_neg == 0))
					count += padding(min_width_size - len(string));
				while (*string)
					_fputchar(*string++), count++;
				if ((flag_width == 1) && (len(string) < min_width_size) && (flag_neg == 1))
					count += padding(min_width_size - len(string));
				break;
			}
			if (flag_width == 1)
				foo = _print_hex_count((unsigned long int)string, 0) + 2;
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
				count += padding(min_width_size - foo);
			_fputchar('0'), count++;
			_fputchar('x'), count++;
			count += _print_hex((unsigned long int)string, 0);
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 1))
				count += padding(min_width_size - foo);
			break;
		case 'r':
			string = va_arg(ap, char*);
			if (string == NULL)
				string = "(llun)";
			temp_string = string;
			while (*temp_string++)
				++str_len;
			for (q = str_len - 1; q >= 0; q--)
				_fputchar(string[q]), count++;
			break;
		case 'R':
			string = va_arg(ap, char*);
			if (string == NULL)
			{
				string = "(null)";
				while (*string)
					_fputchar(*string++), count++;
				break;
			}
			while (*string)
			{
				if ((*string >= 'a' && *string <= 'm') || (*string >= 'A'
							&& *string <= 'M'))
					_fputchar((*string++) + 13), count++;
				else if ((*string >= 'n' && *string <= 'z') || (*string >= 'N'
							&& *string <= 'Z'))
					_fputchar((*string++) - 13), count++;
				else
					_fputchar(*string++), count++;
			}
			break;
		case ' ':
			percent_space++;
			if ((percent_space % 2) == 0)
			{
				_fputchar('%'), count++;
				_fputchar(format[i]), count++;
			}
			break;
		default:
			_fputchar('%'), count++;
			if (no_lh != 1)
				_fputchar(format[i]), count++;
		}
		}
		if (flag_width == 1 && flag_star == 0)
			free(width);
		if (flag_precision == 1 && flag_star_p == 0)
			free(precision);
		flag_index = flag_plus = flag_space = flag_hash = flag_zero = 0;
		flag_neg = flag_width = flag_precision = flag_star = 0;
		flag_star_p = flag_ell = flag_h = no_lh = foo = bar = pre = 0;
		min_precision = 0, zpad = 0, x = 0, y = 0, z = 0;
		min_width_size = 0, t = 0, p = 0, str_len = 0;
		i++;
	}
	_fputchar(-1);
	va_end(ap);
	if (percent_space == 1)
		return (-1);
	return (count);
}

/**
 * _fputchar - print a char to stdout
 * @c: the char
 *
 * Return: void
 */
void _fputchar(char c)
{
	static char buf[1024];
	static int buf_count;

	if (c == -1 || buf_count >= 1024)
	{
		write(2, buf, buf_count);
		buf_count = 0;
	}
	if (c != -1)
	{
		buf[buf_count] = c;
		buf_count++;
	}
}
