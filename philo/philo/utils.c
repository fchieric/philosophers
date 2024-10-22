/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 03:59:18 by fabi              #+#    #+#             */
/*   Updated: 2024/10/22 02:29:35 by fabi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return i;
}

void error_exit(char *message)
{
	write(2, message, ft_strlen(message));
	exit(1);
}

int is_valid_digit(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

long parse_number(const char *str, int *i, int *found_digit)
{
	long res;

	res = 0;
	*found_digit = 0;
	while (str[*i] && (is_valid_digit(str[*i]) || str[*i] == ' '))
	{
		if (is_valid_digit(str[*i]))
		{
			if (res > INT_MAX / 10 || (res == INT_MAX / 10 && 
				(str[*i] - '0') > INT_MAX % 10))
			{
				error_exit("Error: Number exceeds INT_MAX 🥵\n");
			}
			res = res * 10 + (str[*i] - '0');
			*found_digit = 1;
		}
		(*i)++;
	}
	return res;
}

long ft_atol(const char *str)
{
	int i;
	int found_digit;
	long res;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			error_exit("Error: Negative numbers not allowed 😡\n");
		i++;
	}
	res = parse_number(str, &i, &found_digit);
	if (!found_digit)
		error_exit("Error: Found a non number 🤯\n");
	if (str[i] != '\0')
		error_exit("Error: Invalid characters in input 🥶\n");
	return res;
}
