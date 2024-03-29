/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:24:37 by nfurlani          #+#    #+#             */
/*   Updated: 2024/03/09 17:06:04 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int is_delimiter(char c)
{
    return (c == '|' || c == '>' || c == '<');
}

int count_tokens(char *str)
{
    int		tokens;
    char	prev;
	int		i;

	tokens = 0;
	prev = '\0';
	i = -1;

	while (str[++i] != '\0')
	{
		if (is_delimiter(str[i]))
		{
			if (i == 0 || is_delimiter(prev) == 0 || prev != str[i])
				tokens++;
		}
		else if (i == 0 || is_delimiter(prev))
			tokens++;
		prev = str[i];
	}
    return tokens;
}

char *next_token(char **str)
{
    char	*start;
    char	*end;
    int		isDelim;
	char	*token;

	start = *str;
	end = start;
	isDelim = is_delimiter(**str);
    while (*end && ((isDelim && is_delimiter(*end)) || (!isDelim && !is_delimiter(*end))))
        	end++;
    if (isDelim && *end == *start)
        end++;
    token = malloc((end - start) + 1);
    ft_strncpy(token, start, end - start);
    token[end - start] = '\0';
    *str = end;
    return token;
}

char **ft_split(char *str)
{	
	int		i;
    int		n;
	char	**tokens;

	i = 0;
	n = count_tokens(str);
    tokens = malloc((n + 1) * sizeof(char*));
	while (i < n)
	{
		tokens[i] = next_token(&str);
		i++;
	}
    tokens[n] = NULL;
    return tokens;
}

int main() {
    char *test_str = "|gvgh<hbui<<gyui>>";
    char **tokens = ft_split(test_str);

    for (int i = 0; tokens[i] != NULL; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
        free(tokens[i]); // Ricorda di liberare ogni token
    }
    free(tokens); // E l'array di token

    return 0;
}
