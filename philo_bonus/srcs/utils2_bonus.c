/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:08:27 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/04 11:13:35 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

long		ft_atol(const char *str)
{
	int			i;
	int			j;
	int			h;
	long int	final;

	i = 0;
	j = 0;
	final = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			j++;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		h = str[i] - 48;
		final = (final * 10) + h;
		i++;
	}
	if (j % 2 == 1)
		final *= -1;
	return (final);
}

static int	ft_lennbr(long n, int sign)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (sign == -1)
		len++;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_putnbr(char *str, int len, long n)
{
	while (n > 0)
	{
		str[len--] = 48 + (n % 10);
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(long n)
{
	int		sign;
	int		len;
	char	*str;

	sign = 1;
	if (n < 0)
	{
		n = -n;
		sign = -1;
	}
	len = ft_lennbr(n, sign);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (sign == -1)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	str = ft_putnbr(str, len, n);
	return (str);
}
