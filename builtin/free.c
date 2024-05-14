/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:40:32 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/14 19:17:10 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_lexer *lexer, t_env *env)
{
	if (ft_strcmp(lexer->str, "exit") == 0)
	{
		ft_free_env(env);
		ft_free_lexer(&lexer);
		exit(0);
	}
	return (0);
}

void	ft_free_env(t_env *env)
{
	t_env	*temp;

	temp = NULL;
	while (env)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;
	}
}

void	ft_free_lexer(t_lexer **lexer)
{
	t_lexer		*temp;

	while (*lexer)
	{
		temp = (*lexer)->next;
		if ((*lexer)->str)
			free((*lexer)->str);
		if ((*lexer)->token)
			free((*lexer)->token);
		free(*lexer);
		*lexer = temp;
	}
	free(*lexer);
}

void	ft_free(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i])
			free(temp[i]);
		i++;
	}
	free(temp);
}
