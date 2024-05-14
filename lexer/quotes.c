/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:44:21 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/14 11:50:02 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_quotes(char **temp)
{
	int	j;
	int	count_one;
	int	count_two;

	j = 0;
	while (temp[j])
	{
		count_one = count_quotes(temp[j], '"');
		count_two = count_quotes(temp[j], '\'');
		if (count_one == 0 && count_two == 0)
			j++;
		else if (count_one == 1 || count_two == 1)
			j++;
		else
		{
			remove_char(temp[j], '"', count_one);
			remove_char(temp[j], '\'', count_two);
			j++;
		}
	}
	single_quote(temp);
}

int	count_quotes(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	remove_char(char *str, char c, int count)
{
	char	*s_read;
	char	*s_write;
	int		skip_first;
	int		skipped;

	s_read = str;
	s_write = str;
	skip_first = (count % 2 != 0);
	skipped = 0;
	while (*s_read)
	{
		if (*s_read == c)
		{
			if (skip_first && (skipped == 0 || count - skipped == 1))
				skipped++;
			else
				*s_write++ = *s_read;
		}
		else
			*s_write++ = *s_read;
		s_read++;
	}
	*s_write = '\0';
}

void	manage_quote(char **temp, char c)
{
	char	*input;
	int		j;

	j = 0;
	while (temp[j])
		j++;
	while (1)
	{
		input = readline("dquote> ");
		if (*input)
		{
			temp[j] = ft_strdup(input);
			if (ft_strchr(temp[j], c))
			{
				temp[j + 1] = 0;
				return ;
			}
			j++;
		}
	}
}

void	single_quote(char **temp)
{
	int	j;
	int	count_one;
	int	count_two;

	j = 0;
	count_one = 0;
	count_two = 0;
	while (temp[j])
	{
		count_one += count_quotes(temp[j], '"');
		count_two += count_quotes(temp[j], '\'');
		j++;
	}
	if (count_one % 2 != 0)
		manage_quote(temp, '"');
	else if (count_two % 2 != 0)
		manage_quote(temp, '\'');
}
