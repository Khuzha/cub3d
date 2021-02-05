int		main_func(const char *str, int level, int pos, int result)
{
	int counter;
	int cur;

	counter = 0;
	if (str[counter] == '-')
	{
		pos = 0;
		counter++;
	}
	while (str[counter] != '\0' &&
			str[counter] >= '0' && str[counter] <= '9')
		counter++;
	counter--;
	while (counter != -2)
	{
		if (str[counter] < '0' || str[counter] > '9')
			break ;
		cur = (str[counter] - 48) * level;
		if (cur < result && cur != 0)
			return (pos ? -1 : 0);
		result += cur;
		level *= 10;
		counter--;
	}
	return (pos ? result : result * -1);
}

int		middleware(const char *str, int level, int pos, int result)
{
	while (*str < '0' || *str > '9')
	{
		if (*str != ' ' && *str != '\t' && *str != '\n' &&
				*str != '\v' && *str != '\f' && *str != '\r' &&
				*str != '-' && *str != '+')
			return (0);
		if (*str == '-')
			pos = 0;
		if (*str == '-' && (str[1] < '0' || str[1] > '9'))
			return (0);
		if ((*str == '-' || *str == '+') &&
				(str[1] == '-' || str[1] == '+'))
			return (0);
		str++;
	}
	result = main_func(str, level, pos, result);
	return (result);
}

int		ft_atoi(const char *str)
{
	int result;
	int level;
	int pos;

	result = 0;
	level = 1;
	pos = 1;
	result = middleware(str, level, pos, result);
	return (result);
}
