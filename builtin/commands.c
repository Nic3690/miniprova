/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:53:40 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/12 17:45:50 by nfurlani         ###   ########.fr       */
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

void	builtin_pwd(t_lexer **lexer)
{
	char	cwd[1024];

	if (ft_strcmp((*lexer)->str, "pwd") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)))
			printf ("%s\n", cwd);
		else
			perror((*lexer)->str);
	}
}

void	builtin_echo(t_lexer **lexer)
{
	int	flag;

	flag = 1;
	if (ft_strcmp((*lexer)->str, "echo") == 0)
	{
		*lexer = (*lexer)->next;
		if (ft_strcmp((*lexer)->str, "") == 0)
		{
			printf ("\n");
			return ;
		}
		if (*lexer && ft_strcmp((*lexer)->str, "-n") == 0)
		{
			flag = 0;
			*lexer = (*lexer)->next;
		}
		while (*lexer && (*lexer)->next)
		{
			printf ("%s ", (*lexer)->str);
			*lexer = (*lexer)->next;
		}
		if (*lexer)
			printf ("%s", (*lexer)->str);
		if (flag)
			printf ("\n");
	}
}

void	bultin_unset(t_lexer **lexer, t_export **export)
{
	t_export	*prev_export;
	t_export	*head;

	prev_export = NULL;
	head = *export;
	if (del_first(lexer, export))
		return ;
	if (ft_strcmp((*lexer)->str, "unset") == 0)
	{
		while (*export != NULL && ft_strcmp((*export)->key, (*lexer)->next->str) != 0)
		{
        	prev_export = *export;
        	*export = (*export)->next;
    	}
		if (*export == NULL)
			return ;
		prev_export->next = (*export)->next;
		free((*export)->key);
		free((*export)->value);
		free(*export);
	}
	*export = head;
}

int	del_first(t_lexer **lexer, t_export **export)
{
	t_export	*temp;

	temp = *export;
	if (temp != NULL && ft_strcmp(temp->key, (*lexer)->next->str) == 0)
	{
    	temp = (*export)->next;
        free((*export)->key);
        free((*export)->value);
        free(*export);
		(*export) = temp;
		return (1);
    }
	return (0);
}
