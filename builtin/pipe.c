/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:11:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/04 19:01:28 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_command(t_lexer **lexer, t_envp_struct *envp_struct, char **envp)
{
	char	**full_temp;
	t_lexer	**head;

	head = lexer;
	full_temp = new_full_temp(lexer);
	if (!check_pipe(lexer) && !check_redirection(lexer))
	{
		if (manage_builtin(lexer, envp_struct) != 1)
			command_execve(full_temp, envp, envp_struct);
		lexer = head;
		return (ft_free(full_temp));
	}
	else if (!check_pipe(lexer) && check_redirection(lexer))
	{
		manage_redirections(lexer, envp_struct, envp);
		lexer = head;
		return (ft_free(full_temp));
	}
	else
	{
		set_fork(lexer, envp_struct, envp);
		lexer = head;
		return (ft_free(full_temp));
	}
}

void	set_fork(t_lexer **lexer, t_envp_struct *envp_struct, char **envp)
{
	t_fd	*fd;

	fd = malloc(sizeof(t_fd));
	fd->pid = -1;
	pipe(fd->fd);
	if (pipe(fd->fd) == -1)
	{
        perror("pipe");
        exit(EXIT_FAILURE);
    }
	fd->pid = fork();
	if (fd->pid == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
	if (fd->pid == 0)
		child(lexer, envp_struct, envp, fd);
	father(lexer, envp_struct, envp, fd);
	free(fd);
}

void	child(t_lexer **lexer, t_envp_struct *envp_struct, char **envp, t_fd *fd)
{
	t_lexer	*start;
	char	**temp;

	start = new_start(lexer);
	temp = new_temp(start);
	close(fd->fd[0]);
	dup2(fd->fd[1], STDOUT_FILENO);
	close(fd->fd[1]);
	if (check_redirection(lexer))
		manage_redirections(lexer, envp_struct, envp);
	else
	{
		if (manage_builtin(&start, envp_struct) != 1)
			command_execve(temp, envp, envp_struct);
	}
	free(start);
	ft_free(temp);
	exit(EXIT_SUCCESS);
}

void	father(t_lexer **lexer, t_envp_struct *envp_struct, char **envp, t_fd *fd)
{
	char	**temp_full;

	while (*lexer && !(ft_strchr((*lexer)->token, '|')))
		*lexer = (*lexer)->next;
	*lexer = (*lexer)->next;
	temp_full = new_full_temp(lexer);
	close(fd->fd[1]);
	dup2(fd->fd[0], STDIN_FILENO);
	close(fd->fd[0]);
	if (check_pipe(lexer))
		set_fork(lexer, envp_struct, envp);
	else if (check_redirection(lexer))
		manage_redirections(lexer, envp_struct, envp);
	else
		if (manage_builtin(lexer, envp_struct) != 1)
			command_execve(temp_full, envp, envp_struct);
}

	// write (1, (*lexer)->str, ft_strlen((*lexer)->str));
	/*ls | grep .txt > files.txt*/