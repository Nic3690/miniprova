/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:44:21 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/05 11:40:51 by nfurlani         ###   ########.fr       */
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

void remove_char(char *str, char c, int count) {
    char *s_read = str;
    char *s_write = str;
    int skip_first = (count % 2 != 0);  // True if odd number of quotes
    int skipped = 0;  // To keep track of how many quotes we've skipped

    while (*s_read) {
        if (*s_read == c) {
            if (skip_first && (skipped == 0 || count - skipped == 1)) {
                // Skip the first and the last quote if odd number of quotes
                skipped++;  // Increment the skipped count
            } else {
                // Otherwise, write the quote to the output
                *s_write++ = *s_read;
            }
        } else {
            *s_write++ = *s_read;  // Always write non-quote characters
        }
        s_read++;
    }
    *s_write = '\0';  // Null-terminate the modified string
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
