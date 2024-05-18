/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:11:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/18 16:14:41 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_fd	*init_fd(void)
{
    t_fd	*fd;

	fd = malloc(sizeof(t_fd));
	if (!fd)
		exit(EXIT_FAILURE);
	fd->temp = dup(0);
	fd->pid = 0;
	return (fd);
}

void	split_command(t_lexer **lexer, t_env *env, char **envp)
{
	t_lexer	*start;
	t_lexer	*head;
	t_fd	*fd;

	head = *lexer;
	fd = init_fd();
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
	free(fd);
	*lexer = head;
}

void set_fork(t_lexer **start, t_fd *fd, t_env *env, char **envp)
{
    if (pipe(fd->fd) == -1)
        exit(EXIT_FAILURE);
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
		close(fd->fd[0]);
		dup2(fd->fd[1], STDOUT_FILENO);
		close(fd->fd[1]);
        child(start, fd, env, envp);
	}
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
		dup2(fd->temp, STDIN_FILENO);
		close(fd->temp);
		dup2(fd->fd[1], STDOUT_FILENO);
		close(fd->fd[1]);
		close(fd->fd[0]);
	}
	if (manage_builtin(start, env) != 1)
		command_execve(temp, envp);
	else
		exit(EXIT_SUCCESS);
	ft_free(temp);
	ft_free_lexer(&command);
}
