/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:46:54 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/28 17:27:43 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*new_start_redirection(t_lexer **lexer)
{
	t_lexer *start;
	t_lexer	*head;
	t_lexer *start_head;

	head = *lexer;
	start = malloc(sizeof(t_lexer));
	start_head = start;
	while (*lexer && (*lexer)->next)
	{	
		while (!ft_strchr((*lexer)->token, '>') && !ft_strchr((*lexer)->token, '<'))
		{
			start->str = ft_strdup((*lexer)->str);
			start->index = 0;
			start->token = "";
			start->next = malloc(sizeof(t_lexer));
			start = start->next;
			*lexer = (*lexer)->next;
		}
		*lexer = (*lexer)->next;
	}
	*lexer = head;
	start = start_head;
	return (start);
}

char	**new_temp_redirection(t_lexer *start)
{
	t_lexer	*head;
	char	**temp;
	int		i;

	head = start;
	i = 0;
	temp = malloc(sizeof(char *) * 1024 + 1);
	while (start)
	{
		temp[i++] = start->str;
		start = start->next;
	}
	temp[i] = NULL;
	start = head;
	return (temp);
}

int	count_lexer(t_lexer **lexer)
{
	int		i;
	t_lexer	*head;

	i = 0;
	head = *lexer;
	while((*lexer))
	{
		*lexer = (*lexer)->next;
		i++;
	}
	*lexer = head;
	return (i);
}

void	manage_redirections(t_lexer **lexer, t_envp_struct *envp_struct, char **envp)
{
	t_lexer	*head;
	int		fd;

	head = *lexer;
	fd = 0;
	while (*lexer)
	{
		if (ft_strchr((*lexer)->token, '>') || ft_strchr((*lexer)->token, '<'))
		{
			if (count_lexer(lexer) > 2)
			{
				printf ("%s: %s: No such file or directory\n", head->str, (*lexer)->next->str);
				return ;
			}
		}
		*lexer = (*lexer)->next;
	}
	*lexer = head;
	redirection_out(lexer, envp_struct, envp, fd);
	*lexer = head;
	redirection_in(lexer, envp_struct, envp, fd);
	*lexer = head;
	// else if (ft_strchr((*lexer)->token, '>>'))
	// 	redirection_append;
}

void	redirection_out(t_lexer **lexer, t_envp_struct *envp_struct, char **envp, int fd)
{
	t_lexer	*start;
	int		copy;
	char	**temp;

	copy = dup(STDOUT_FILENO);
	start = new_start_redirection(lexer);
	temp = new_temp_redirection(start);
	while (*lexer)
	{
		if (ft_strchr((*lexer)->token, '>'))
		{
			fd = open((*lexer)->next->str, O_CREAT | O_WRONLY, 0644);
			if (fd < 0)
				return (perror("minishell: redir_out: error while opening the file\n"));
			dup2(fd, STDOUT_FILENO);
			close(fd);
			if (manage_builtin(&start, envp_struct) != 1)
				command_execve(temp, envp);
			dup2(copy, STDOUT_FILENO);
			close(copy);
		}
		*lexer = (*lexer)->next;
	}
}

void	redirection_in(t_lexer **lexer, t_envp_struct *envp_struct, char **envp, int fd)
{
	t_lexer	*start;
	char	**temp;

	start = new_start_redirection(lexer);
	temp = new_temp_redirection(start);
	while (*lexer)
	{
		if (ft_strchr((*lexer)->token, '<'))
		{
			fd = open((*lexer)->next->str, O_RDONLY);
			if (fd < 0)
				return perror("minishell: redir_in: error while opening the file\n");
			dup2(fd, STDIN_FILENO);
			close(fd);
			if (manage_builtin(&start, envp_struct) != 1)
				command_execve(temp, envp);
		}
		*lexer = (*lexer)->next;
	}
}
/*comando < file.txt*/