#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

void _putchar(char c);
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
int _printf(const char *format, ...)
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
			_putchar(format[i]), count++;
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
			_putchar(va_arg(ap, int)), count++;
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
				_putchar(*string++), count++;
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
			_putchar('%'), count++;
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
				_putchar('+'), count++;
			if (flag_space == 1 && num >= 0 && flag_plus == 0)
				_putchar(' '), count++;
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
				_putchar('+'), count++;
			if (flag_space == 1 && num >= 0 && flag_plus == 0)
				_putchar(' '), count++;
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
				_putchar('0'), count++;
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
				_putchar('0'), count++;
				_putchar('x'), count++;
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
				_putchar('0'), count++;
				_putchar('X'), count++;
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
						count += _printf("\\x0%X", *string++);
					else
						count += _printf("\\x%X", *string++);
				}
				else
				{
					_putchar(*string++), count++;
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
					_putchar(*string++), count++;
				if ((flag_width == 1) && (len(string) < min_width_size) && (flag_neg == 1))
					count += padding(min_width_size - len(string));
				break;
			}
			if (flag_width == 1)
				foo = _print_hex_count((unsigned long int)string, 0) + 2;
			if ((flag_width == 1) && (foo < min_width_size) && (flag_neg == 0))
				count += padding(min_width_size - foo);
			_putchar('0'), count++;
			_putchar('x'), count++;
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
				_putchar(string[q]), count++;
			break;
		case 'R':
			string = va_arg(ap, char*);
			if (string == NULL)
			{
				string = "(null)";
				while (*string)
					_putchar(*string++), count++;
				break;
			}
			while (*string)
			{
				if ((*string >= 'a' && *string <= 'm') || (*string >= 'A'
							&& *string <= 'M'))
					_putchar((*string++) + 13), count++;
				else if ((*string >= 'n' && *string <= 'z') || (*string >= 'N'
							&& *string <= 'Z'))
					_putchar((*string++) - 13), count++;
				else
					_putchar(*string++), count++;
			}
			break;
		case ' ':
			percent_space++;
			if ((percent_space % 2) == 0)
			{
				_putchar('%'), count++;
				_putchar(format[i]), count++;
			}
			break;
		default:
			_putchar('%'), count++;
			if (no_lh != 1)
				_putchar(format[i]), count++;
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
	_putchar(-1);
	va_end(ap);
	if (percent_space == 1)
		return (-1);
	return (count);
}

/**
 * _putchar - print a char to stdout
 * @c: the char
 *
 * Return: void
 */
void _putchar(char c)
{
	static char buf[1024];
	static int buf_count;

	if (c == -1 || buf_count >= 1024)
	{
		write(1, buf, buf_count);
		buf_count = 0;
	}
	if (c != -1)
	{
		buf[buf_count] = c;
		buf_count++;
	}
}

/**
 * str_to_num - convert a string to an integer
 * @s: string input
 * Return: int
 */
unsigned long int str_to_num(char *s)
{
	int i = 0, j, n = 0;
	unsigned long int m, sum = 0;

	while (*(s + i) != '\0')
		i++;
	for (j = i - 1; j >= 0; j--)
	{
		m = ((int) *(s + j) - (int) '0');
		m = m * _power(10, n);
		sum = sum + m;
		n++;
	}
	return (sum);
}

/**
 * _power - return base num raise to the power of exponent num
 * @base: the base num
 * @exponent: the exponent num
 * Return: int
 */
int _power(int base, int exponent)
{
	int result = 1;
	int raise;

	for (raise = exponent; raise > 0; raise--)
	{
		result = result * base;
	}
	return (result);
}

/**
 * _print_num - print a decimal number to stdout
 * @num: the number to print
 * @zero_padding: the number of zeros to pad when precision is set
 *
 * Return: void
 */
int _print_num(long int num, int zero_padding)
{
	int j = 0, neg = 0, min = 0, count = 0;
	long int temp;
	char *tmp_str;

	temp = num;
	if (temp < 0)
	{
		if (temp == LONG_MIN)
		{
			temp = LONG_MIN + 1;
			min = 1;
		}
		num = temp =  0 - temp, neg = 1;
	}
	while (temp > 9)
		temp /= 10, ++j;
	++j;
	tmp_str = malloc((j + 1) * sizeof(char));
	if (tmp_str == NULL)
		exit(-1);
	tmp_str[j] = '\0';
	if (min == 1)
	{
	tmp_str[--j] = (num % 10) + 1 + '0';
	num /= 10;
	}
	while (j)
	{
		tmp_str[--j] = (num % 10) + '0';
		num /= 10;
	}
	if (neg == 1)
		_putchar('-'), count++;
	while (zero_padding--)
	{
		_putchar('0'), count++;
	}
	while (*tmp_str)
		_putchar(*tmp_str++), count++;
	return (count);
}
/**
 * _print_bin - converts an unsigned int to binary and prints to stdout
 * @num: the unsigned int
 * @count: counts number of characters printed
 *
 * Return: number of characters printed
 */
int _print_bin(unsigned int num, int count)
{
	unsigned int i = 0, temp;
	char *tmp_bin;

	if (num == 0)
	{
		_putchar('0'), count++;
	}
	temp = num;
	while (num)
	{
		num /= 2;
		++i;
	}
	tmp_bin = malloc((i + 1) * sizeof(char));
	if (tmp_bin == NULL)
		exit(-1);
	tmp_bin[i] = '\0';
	while (i)
	{
		tmp_bin[--i] = (temp % 2) + '0';
		temp /= 2;
	}
	while (*tmp_bin)
		_putchar(*tmp_bin++), count++;
	return (count);
}
/**
 * _print_unsigned_num - print a decimal number to stdout
 * @num: the number to print
 *
 * Return: void
 */
int _print_unsigned_num(unsigned long int num)
{
	int j = 0, count = 0;
	unsigned long int temp;
	char *tmp_str;

	temp = num;
	while (temp > 9)
		temp /= 10, ++j;
	++j;
	tmp_str = malloc((j + 1) * sizeof(char));
	if (tmp_str == NULL)
		exit(-1);
	tmp_str[j] = '\0';
	while (j)
	{
		tmp_str[--j] = (num % 10) + '0';
		num /= 10;
	}
	while (*tmp_str)
		_putchar(*tmp_str++), count++;
	return (count);
}
/**
 * _print_octal - converts an unsigned int to octal and prints to stdout
 * @num: the unsigned int
 *
 * Return: number of characters printed
 */
int _print_octal(unsigned long int num)
{
	int i = 0, count = 0;
	unsigned long int temp;
	char *tmp_oct;

	if (num == 0)
	{
		_putchar('0'), count++;
	}
	temp = num;
	while (num)
	{
		num /= 8;
		++i;
	}
	tmp_oct = malloc((i + 1) * sizeof(char));
	if (tmp_oct == NULL)
		exit(-1);
	tmp_oct[i] = '\0';
	while (i)
	{
		tmp_oct[--i] = (temp % 8) + '0';
		temp /= 8;
	}
	while (*tmp_oct)
		_putchar(*tmp_oct++), count++;
	return (count);
}
/**
 * _print_hex - converts an unsigned int to hexadecimal and prints to stdout
 * @num: the unsigned int
 * @flag: 0 if lower and 1 if upper
 *
 * Return: number of characters printed
 */
int _print_hex(unsigned long int num, int flag)
{
	int i = 0, count = 0;
	unsigned long int temp;
	char *tmp_hex;
	char *hex_num;

	hex_num = "abcdefABCDEF";
	if (num == 0)
	{
		_putchar('0'), count++;
	}
	temp = num;
	while (num)
	{
		num /= 16;
		++i;
	}
	tmp_hex = malloc((i + 1) * sizeof(char));
	if (tmp_hex == NULL)
		exit(-1);
	tmp_hex[i] = '\0';
	while (i)
	{
		if ((temp % 16) > 9)
		{
			if (flag == 0)
				tmp_hex[--i] = hex_num[(temp % 16) - 10];
			else
				tmp_hex[--i] = hex_num[(temp % 16) - 10 + 6];
		}
		else
		{
			tmp_hex[--i] = (temp % 16) + '0';
		}
		temp /= 16;
	}
	while (*tmp_hex)
		_putchar(*tmp_hex++), count++;
	return (count);
}
/**
 * is_flag - function to check if a char is a flag character
 * @c: the character
 *
 * Return: 1 if flag char, 0 otherwise
 */
int is_flag(char c)
{
	char *flags;

	flags = "+ #0-";
	while (*flags)
	{
		if (c == *flags++)
			return (1);
	}
	return (0);
}
/**
 * is_format - function to check if a char is a format specifier
 * @c: the character
 *
 * Return: 1 if format, 0 otherwise
 */
int is_format(char c)
{
	char *formats;

	formats = "csdiuoxXp";
	while (*formats)
	{
		if (c == *formats++)
			return (1);
	}
	return (0);
}
/**
 * padding - function to print padding of space or zeros
 * @pad_width: the size of padding
 *
 * Return: number of chars printed
 */
int padding(int pad_width)
{
	int i;

	for (i = 0; i < pad_width; i++)
		_putchar(' ');
	return (pad_width);
}
/**
 * zero_padding - function to print padding of zeros
 * @pad_width: the size of padding
 *
 * Return: number of chars printed
 */
int zero_padding(int pad_width)
{
	int i;

	for (i = 0; i < pad_width; i++)
		_putchar('0');
	return (pad_width);
}
/**
 * len - function to compute length of a string
 * @str: the pointer to string
 *
 * Return: length of string
 */
int len(char *str)
{
	int i = 0;

	while (*str++)
		i++;
	return (i);
}
/**
 * _print_num_count - count no of chars printed to stdout
 * @num: the number to print
 *
 * Return: void
 */
int _print_num_count(long int num)
{
	int j = 0, neg = 0, min = 0, count = 0;
	long int temp;
	char *tmp_str;

	temp = num;
	if (temp < 0)
	{
		if (temp == LONG_MIN)
		{
			temp = LONG_MIN + 1;
			min = 1;
		}
		num = temp =  0 - temp, neg = 1;
	}
	while (temp > 9)
		temp /= 10, ++j;
	++j;
	tmp_str = malloc((j + 1) * sizeof(char));
	if (tmp_str == NULL)
		exit(-1);
	tmp_str[j] = '\0';
	if (min == 1)
	{
	tmp_str[--j] = (num % 10) + 1 + '0';
	num /= 10;
	}
	while (j)
	{
		tmp_str[--j] = (num % 10) + '0';
		num /= 10;
	}
	if (neg == 1)
		count++;
	while (*tmp_str++)
		count++;
	return (count);
}
/**
 * _print_unsigned_num_count - count no of chars printed to stdout
 * @num: the number to print
 *
 * Return: void
 */
int _print_unsigned_num_count(unsigned long int num)
{
	int j = 0, count = 0;
	unsigned long int temp;
	char *tmp_str;

	temp = num;
	while (temp > 9)
		temp /= 10, ++j;
	++j;
	tmp_str = malloc((j + 1) * sizeof(char));
	if (tmp_str == NULL)
		exit(-1);
	tmp_str[j] = '\0';
	while (j)
	{
		tmp_str[--j] = (num % 10) + '0';
		num /= 10;
	}
	while (*tmp_str++)
		count++;
	return (count);
}
/**
 * _print_octal_count - counts no of chars in octal printed to stdout
 * @num: the unsigned int
 *
 * Return: number of characters printed
 */
int _print_octal_count(unsigned long int num)
{
	int i = 0, count = 0;
	unsigned long int temp;
	char *tmp_oct;

	if (num == 0)
	{
		count++;
	}
	temp = num;
	while (num)
	{
		num /= 8;
		++i;
	}
	tmp_oct = malloc((i + 1) * sizeof(char));
	if (tmp_oct == NULL)
		exit(-1);
	tmp_oct[i] = '\0';
	while (i)
	{
		tmp_oct[--i] = (temp % 8) + '0';
		temp /= 8;
	}
	while (*tmp_oct++)
		count++;
	return (count);
}
/**
 * _print_hex_count - counts the no of chars in hexadecimal printed to stdout
 * @num: the unsigned int
 * @flag: 0 if lower and 1 if upper
 *
 * Return: number of characters printed
 */
int _print_hex_count(unsigned long int num, int flag)
{
	int i = 0, count = 0;
	unsigned long int temp;
	char *tmp_hex;
	char *hex_num;

	hex_num = "abcdefABCDEF";
	if (num == 0)
	{
		count++;
	}
	temp = num;
	while (num)
	{
		num /= 16;
		++i;
	}
	tmp_hex = malloc((i + 1) * sizeof(char));
	if (tmp_hex == NULL)
		exit(-1);
	tmp_hex[i] = '\0';
	while (i)
	{
		if ((temp % 16) > 9)
		{
			if (flag == 0)
				tmp_hex[--i] = hex_num[(temp % 16) - 10];
			else
				tmp_hex[--i] = hex_num[(temp % 16) - 10 + 6];
		}
		else
		{
			tmp_hex[--i] = (temp % 16) + '0';
		}
		temp /= 16;
	}
	while (*tmp_hex++)
		count++;
	return (count);
}
