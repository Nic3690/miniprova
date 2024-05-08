/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:53:05 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/08 15:38:49 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_heredoc(t_lexer **lexer)
{
	t_lexer	*head;
	char	*str;

	head = *lexer;
	while ((*lexer) && (*lexer)->next)
	{
		if (ft_strcmp((*lexer)->token, "<<") == 0)
		{
			str = ft_strdup((*lexer)->next->str);
			(*lexer)->next->str = ft_strdup("");
			readline_heredoc(str, lexer);
			((*lexer)->next->str) = ft_strjoin(((*lexer)->next->str), "\n");
		}
		*lexer = (*lexer)->next;
	}
	*lexer = head;
}

void	readline_heredoc(char *str, t_lexer **lexer)
{
	char	*input;
	
	while (1)
	{
		input = readline("heredoc> ");
		if (*input)
		{
			if (ft_strcmp(input, str) == 0)
			{
				free((*lexer)->token);
				(*lexer)->token = "<<";
				break ;
			}
			((*lexer)->next->str) = ft_strjoin_heredoc((*lexer)->next->str, input);
		}
	}
}

void	redirection_heredoc(t_lexer **lexer, t_envp_struct *envp_struct, char **envp)
{
	t_lexer	*start;
	char	**temp;
	char	*file_name;

	file_name = ft_strdup("file.txt");
	start = new_start_redirection(lexer);
	temp = new_temp_redirection(start);
	while (*lexer)
	{
		if (ft_strcmp((*lexer)->token, "<<") == 0)
		{
			manage_fd_heredoc(file_name, lexer);
			if (manage_builtin(&start, envp_struct) != 1)
				command_execve(temp, envp);
			break ;
		}
		*lexer = (*lexer)->next;
	}
	unlink(file_name);
	free(file_name);
	ft_free(temp);
	ft_free_lexer(&start);
}

void	manage_fd_heredoc(char *file_name, t_lexer **lexer)
{
	int		fd;
	int		copy;

	copy = dup(STDIN_FILENO);
	fd = open(file_name, O_CREAT | O_RDWR, 0664);
	if (fd < 0)
		return perror("minishell: redir_in: error while opening the file\n");
	write(fd, (*lexer)->next->str, ft_strlen((*lexer)->next->str));
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return perror("minishell: redir_in: error while opening the file\n");
	dup2(copy, STDIN_FILENO);
	close(copy);
}

// void	manage_heredoc(t_lexer **lexer)
// {
// 	char	*input;
// 	t_lexer	*head;
// 	char	*str;

// 	head = *lexer;
// 	while ((*lexer))
// 	{
// 		// printf("%s\n", (*lexer)->token);
// 		// 	write(2, "zzz\n", 4);
// 		if (ft_strcmp((*lexer)->token, "<<") == 0)
// 		{
// 			if ((*lexer)->next)
// 			{
// 				str = ft_strdup((*lexer)->next->str);
// 				(*lexer)->next->str = ft_strdup("");
// 			}
// 			while (1)
// 			{
// 				input = readline("heredoc> ");
// 				if (*input)
// 				{
// 					if (ft_strcmp(input, str) == 0)
// 					{
// 						free((*lexer)->token);
// 						// free(str);
// 						(*lexer)->token = ft_strdup("<<");
// 						// free(input);
// 						break ;
// 					}
// 					(*lexer)->next->str = ft_strjoin_heredoc((*lexer)->next->str, input);
// 				}
// 			}
// 			// free(str);
// 		}
// 		*lexer = (*lexer)->next;
// 	}
// 	*lexer = head;
// 	// free(str);
// }
