#include <stdio.h>
#include <stdarg.h>

int	ft_putstr(char *str)
{
	int len = 0;

	if (!str)
		str = "(null)";
	while (*str)
	{
		write(1, str, 1);
		len++;
	}
	return (len);
}

void	ft_putnbr(long long num, int base, int *count)
{
	char	*abc;

	abc = "0123456789abcdef";
	if (num < 0)
	{
		num *= -1;
		count += write(1, "-", 1);
	}
	if (num > base)
		ft_putnbr((num/base), base, count);
	*count += write(1, &abc[num % base], 1);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		count;
	
	count = 0;
	va_start(list, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 's')
				count += ft_putstr(va_arg(list, char *));
			else if (*format == 'd')
				ft_putnbr((long long)va_arg(list, int), 10, &count);
			else if (*format == 'x')
				ft_putnbr((long long)va_arg(list, unsigned int), 16, &count);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(list);
	return (count);
}