/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:11:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/26 17:33:27 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*new_start(t_lexer **lexer)
{
	t_lexer *start;
	t_lexer	*head;
	t_lexer *start_head;

	head = *lexer;
	start = malloc(sizeof(t_lexer));
	start_head = start;
	while (*lexer && (*lexer)->next)
	{	
		while (!ft_strchr((*lexer)->token, '|'))
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

char	**new_temp(t_lexer *start)
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

char	**new_full_temp(t_lexer **lexer)
{
	char	**temp;
	char	**head;
	t_lexer	*head_lexer;
	int		size;

	size = 1024;
	head_lexer = *lexer;
	temp = malloc(sizeof(char *) * size + 1);
	head = temp;
	if (temp == NULL)
		return (NULL);
	while (*lexer)
	{
		*temp = (*lexer)->str;
		*lexer = (*lexer)->next;
		temp++;
	}
	*temp = NULL;
	temp = head;
	*lexer = head_lexer;
	return (temp);
}

int	check_pipe(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	while (*lexer)
	{
		if (ft_strchr((*lexer)->token, '|'))
			return (1);
		*lexer = (*lexer)->next;
	}
	*lexer = head;
	return (0);
}

void	split_command(t_lexer **lexer, t_envp_struct *envp_struct, char **envp)
{
	t_lexer *head;
	char	**full_temp;

	head = *lexer;
	full_temp = new_full_temp(lexer);
	if (!check_pipe(lexer))
	{
		if (manage_builtin(lexer, envp_struct) != 1)
			command_execve(full_temp, envp);
		return ;
	}
	else
	{
		*lexer = head;
		set_fork(lexer, envp_struct, envp);
		return ;
	}
	*lexer = head;
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
}

void	child(t_lexer **lexer, t_envp_struct *envp_struct, char **envp, t_fd *fd)
{
	t_lexer	*start;
	char	**temp;

	start = new_start(lexer);
	temp = new_temp(start);
	printf("%s\n", *temp);
	close(fd->fd[0]);
	dup2(fd->fd[1], STDOUT_FILENO);
	close(fd->fd[1]);
	if (manage_builtin(&start, envp_struct) != 1)
		command_execve(temp, envp);
	free(start);
	free(temp);
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
	if (manage_builtin(lexer, envp_struct) != 1)
		command_execve(temp_full, envp);
}

	// write (1, (*lexer)->str, ft_strlen((*lexer)->str));