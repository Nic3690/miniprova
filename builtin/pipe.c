/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:11:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/17 22:34:09 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_command(t_lexer **lexer, t_env *env, char **envp)
{
    t_fd	*fd;
	t_lexer	*start;
	t_lexer	*head;

	fd = malloc(sizeof(t_fd));
	if (!fd)
	{
        perror("malloc");
        exit(EXIT_FAILURE);
    }
	head = *lexer;
	fd->temp = dup(0);
	fd->pid = 0;
	while (*lexer)
	{
		start = new_start(lexer);
		if ((*lexer)->next == NULL || !check_pipe(lexer))
			last_command(&start, fd, env, envp);
		else
			set_fork(&start, fd, env, envp);
		while (*lexer && ft_strcmp((*lexer)->token, "|") != 0)
			(*lexer) = (*lexer)->next;
		if (*lexer && (*lexer)->token)
			(*lexer) = (*lexer)->next;
		ft_free_lexer(&start);
	}
	close(fd->temp);
	close(fd->fd[1]);
	free(fd);
	*lexer = head;
}

void set_fork(t_lexer **start, t_fd *fd, t_env *env, char **envp)
{
    if (pipe(fd->fd) == -1)
	{
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    fd->pid = fork();
	signal(SIGINT, handle_child);
	signal(SIGQUIT, handle_child);
    if (fd->pid == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (fd->pid == 0)
        child(start, fd, env, envp);
    else
	{
		close(fd->temp);
		close(fd->fd[1]);
		fd->temp = fd->fd[0];
    }
}

void	child(t_lexer **start, t_fd *fd, t_env *env, char **envp)
{
	char	**temp;
	t_lexer	*command;

	command = new_start_redirection(start);
	temp = new_temp_redirection(command);
	if (check_redirection(start))
		manage_redirections(start, fd, 1);
	else
	{
		dup2(fd->fd[1], STDOUT_FILENO);
		close(fd->fd[0]);
		dup2(fd->temp, STDIN_FILENO);
		close(fd->temp);
	}
	if (manage_builtin(start, env) != 1)
		command_execve(temp, envp);
	else
		exit(EXIT_SUCCESS);
	ft_free(temp);
	ft_free_lexer(&command);
}

void	last_command(t_lexer **start, t_fd *fd, t_env *env, char **envp)
{
	char	**temp;
	t_lexer *command;

	command = new_start_redirection(start);
	temp = new_temp_redirection(command);
	fd->pid = fork();
	signal(SIGINT, handle_child);
	signal(SIGQUIT, handle_child);
	if (fd->pid == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
	if (fd->pid == 0)
	{
		if (check_redirection(start))
			manage_redirections(start, fd, 0);
		else
		{
			dup2(fd->temp, STDIN_FILENO);
			close(fd->temp);
		}
		if (manage_builtin(start, env) != 1)
			command_execve(temp, envp);
		else
			exit(EXIT_SUCCESS);
	}
	else
	{
		while (waitpid(-1, &g_exit_code, 0) != -1)
			;
		if (ft_strcmp((*start)->str, "exit") == 0)
			exit (0);
		close(fd->temp);
		fd->temp = dup(0);
	}
	ft_free(temp);
	ft_free_lexer(&command);
}
