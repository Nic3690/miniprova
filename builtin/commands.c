/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:53:40 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/07 12:10:52 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(t_lexer **lexer)
{
	char	cwd[1024];

	if (ft_strcmp((*lexer)->str, "cd") == 0)
	{
		if (chdir((*lexer)->next->str) != 0)
		{
			perror((*lexer)->next->str);
			return (0);
		}
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror((*lexer)->next->str);
			return (0);
		}
		return (1);
	}
	return (0);
}

int	builtin_pwd(t_lexer **lexer)
{
	char	cwd[1024];

	if (ft_strcmp((*lexer)->str, "pwd") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)))
			printf ("%s\n", cwd);
		else
			perror((*lexer)->str);
	}
	return (0);
}

int	builtin_echo(t_lexer **lexer)
{
	if (ft_strcmp((*lexer)->str, "echo") == 0)
	{
		*lexer = (*lexer)->next;
		while (*lexer && (*lexer)->next)
		{
			printf ("%s ", (*lexer)->str);
			*lexer = (*lexer)->next;
		}
		printf ("%s\n", (*lexer)->str);
	}
	return (0);
}