/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:42:49 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/14 11:50:02 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_len(int n)
{
	int	div;
	int	len;

	div = n;
	len = 1;
	if (n < 0)
		len++;
	while (div / 10 != 0)
	{
		div /= 10;
		len++;
	}
	return (len);
}

char	*ft_minint(int n)
{
	char	*s;
	int		len;

	s = malloc(12 * sizeof(char));
	if (n == -2147483648)
	{
		s[0] = '-';
		s[1] = '2';
		n = 147483648;
		s[11] = '\0';
	}
	len = ft_len(n) + 1;
	while (len > 1 && n >= 0)
	{
		s[len] = n % 10 + 48;
		n /= 10;
		len--;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*s;
	int		nb;

	nb = n;
	len = ft_len(n);
	if (n == -2147483648)
		return (ft_minint(n));
	s = malloc((len + 1) * sizeof(char));
	if (s == 0)
		return (0);
	if (n < 0)
		n *= -1;
	s[len] = '\0';
	while (len > 0 && n >= 0)
	{
		s[len - 1] = n % 10 + 48;
		n /= 10;
		len--;
	}
	if (nb < 0)
		s[0] = '-';
	return (s);
}

int	ft_isalnum(int c)
{
	if (((c >= 65) && (c <= 90)) || ((c >= 97)
			&& (c <= 122)) || ((c >= 48) && (c <= 57)))
		return (1);
	else
		return (0);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
