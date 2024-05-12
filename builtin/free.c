/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:40:32 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/10 16:17:50 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(t_lexer *lexer, t_envp_struct *envp_struct)
{
	if (ft_strcmp(lexer->str, "exit") == 0)
	{
		ft_free_env(envp_struct->env);
		ft_free_export(envp_struct->export);
		free(envp_struct);
		ft_free_lexer(&lexer);
		exit(0);
	}
	return (0);
}

void	ft_free_env(t_env **env)
{
	t_env 	**original;
	t_env	*temp;

	original = env;
	temp = NULL;
	while (*env)
	{
		temp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = temp;
	}
	free(original);
}

void	ft_free_export(t_export **export)
{
	t_export 	**original;
	t_export	*temp;

	original = export;
	temp = NULL;
	while (*export)
	{
		temp = (*export)->next;
		free((*export)->key);
		free((*export)->value);
		free(*export);
		*export = temp;
	}
	free(original);
}

void	ft_free_lexer(t_lexer **lexer)
{
	t_lexer		*temp;

	temp = NULL;
	// printf("%s\n", (*lexer)->str);
	// printf("%s\n", (*lexer)->token);
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
		free(temp[i]);
		i++;
	}
	free(temp);
}