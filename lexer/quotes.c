/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:44:21 by nfurlani          #+#    #+#             */
/*   Updated: 2024/03/15 13:29:58 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		/*se la stringa è solo " entra in questo if else*/
		else
		{
			remove_char(temp[j], '"', count_one);
			remove_char(temp[j], '\'', count_two);
			j++;
		}
	}
	single_quote(temp);
}
/*trova le virgolette da eliminare nei punti giusti*/

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
/*conta quanti char c ci sono nella stringa*/

void	remove_char(char *str, char c, int count)
{
	char	*s_read;
	char	*s_write;
	int		leave_one;
	int		found_one;
	int		quote_count;

	s_read = str;
	s_write = str;
	leave_one = (count % 2 != 0);
	found_one = 0;
	quote_count = count_quotes(str, '\'');
	if (c == '\'' && quote_count % 4 != 0 && quote_count % 2 == 0)
		leave_one = 2;
	while (*s_read)
	{
		if (*s_read != c)
			*s_write++ = *s_read;
		else
		{
			if (c == '\'' && (leave_one == 2) && found_one < 2)
			{
				*s_write++ = *s_read;
				found_one++;
			}
			else if (leave_one && !found_one)
			{
				*s_write++ = *s_read;
				found_one = 1;
			}
		}
		s_read++;
	}
	*s_write = '\0';
}
/*accorcia sta cosa*/

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
/*gestione del dquote*/

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
/*funzione per gestire nel qual caso ci fosse una sola virgoletta*/
