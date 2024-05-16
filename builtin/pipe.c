/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:11:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/16 12:54:06 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_command(t_lexer **lexer, t_env *env, char **envp)
{
	char	**full_temp;
	t_lexer	**head;

	head = lexer;
	full_temp = new_full_temp(lexer);
	if (!check_pipe(lexer) && !check_redirection(lexer))
	{
		if (manage_builtin(lexer, env) != 1)
			command_execve(full_temp, envp);
		lexer = head;
	}
	else if (!check_pipe(lexer) && check_redirection(lexer))
	{
		manage_redirections(lexer, env, envp);
		lexer = head;
	}
	else
	{
		set_fork(lexer, env, envp);
		lexer = head;
	}
	return (ft_free(full_temp));
}

void	set_fork(t_lexer **lexer, t_env *env, char **envp)
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
		child(lexer, env, envp, fd);
	father(lexer, env, envp, fd);
	free(fd);
}

void	child(t_lexer **lexer, t_env *env, char **envp, t_fd *fd)
{
	t_lexer	*start;
	char	**temp;

	fd->status = fd->pid;
	start = new_start(lexer);
	temp = new_temp(start);
	close(fd->fd[0]);
	dup2(fd->fd[1], STDOUT_FILENO);
	close(fd->fd[1]);
	if (manage_builtin(&start, env) != 1)
		command_execve(temp, envp);
	free(start);
	ft_free(temp);
	exit(EXIT_SUCCESS);
}

void	father(t_lexer **lexer, t_env *env, char **envp, t_fd *fd)
{
	char	**temp_full;
	int		copy;

	copy = dup(STDIN_FILENO);
	while (*lexer && ft_strcmp((*lexer)->token, "|") != 0)
		*lexer = (*lexer)->next;
	*lexer = (*lexer)->next;
	temp_full = new_full_temp(lexer);
	close(fd->fd[1]);
	dup2(fd->fd[0], STDIN_FILENO);
	close(fd->fd[0]);
	if (check_pipe(lexer))
	{
		set_fork(lexer, env, envp);
		if ((*lexer)->next == NULL)
		{
			while (waitpid(-1, &(fd->status), 0) != -1)
				;
		}
	}
	else if (check_redirection(lexer))
		manage_redirections(lexer, env, envp);
	else
	{
		if (manage_builtin(lexer, env) != 1)
			command_execve(temp_full, envp);
	}
	dup2(copy, STDIN_FILENO);
	close(copy);
	ft_free(temp_full);
}
