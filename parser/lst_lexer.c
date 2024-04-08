/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:19:57 by nfurlani          #+#    #+#             */
/*   Updated: 2024/03/15 13:30:30 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_list(int argc, char **argv)
{
	t_lexer	*lexer;
	int		j;
	char	*token;
	char	*str;

	j = -1;
	lexer = NULL;
	(void)argc;
	while (argv[++j])
	{
		if (ft_check_token(argv[j]))
		{
			token = ft_strdup(argv[j]);
			str = "";
		}
		else
		{
			str = ft_strdup(argv[j]);
			token = "";
		}
		ft_lstadd_back(&lexer, ft_lstnew(str, token));
	}
	return (lexer);
}

int	ft_check_token(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '|') || (str[i] == '>') || (str[i] == '<')
			|| ((str[i] == '<') && (str[i + 1] == '<'))
			|| ((str[i] == '>') && (str[i + 1] == '>')))
			return (1);
		i++;
	}
	return (0);
}

t_lexer	*ft_lstnew(char *str, char *token)
{
	t_lexer	*new;

	new = (t_lexer *)ft_calloc(1, sizeof(t_lexer));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->token = token;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
}

t_lexer	*ft_lstlast(t_lexer *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
