/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:27:09 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/18 13:24:47 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <ctype.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_exit_code;

typedef struct s_lexer
{
	char			*str;
	char			*token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_fd
{
	pid_t			pid;
	int				fd[2];
	int				temp;
}	t_fd;

/*main.c*/
void		reading(t_env *env, char **envp);

/*signal.c*/
void		setup_signals(void);
void		handle_sigint(int signal);
void		handle_child(int signal);
void		handle_sigign(void);

/*free.c*/
int			ft_exit(t_lexer *lexer, t_env *env);
void		ft_free_env(t_env *env);
void		ft_free_lexer(t_lexer **lexer);
void		ft_free(char **temp);

/*parser*/
void		parser(char *str, t_env *env, char **envp);
void		move_redirection(t_lexer **lexer);
t_lexer		*reset_head(t_lexer *lexer);
int			check_spaces(char *str);
void		print_lexer(t_lexer **lexer);

/*quotes.c*/
void		find_quotes(char **temp);
int			count_quotes(char *str, char c);
void		remove_char(char *str, char c, int count);
void		manage_quote(char **temp, char c);
void		single_quote(char **temp);

/*split_token.c*/
char		*ft_strncpy(char *dest, char *src, unsigned int n);
int			is_delimiter(char c);
int			count_tokens(char *str);
char		*next_token(char **str);
char		**ft_token_split(char *str);

/*lst_env.c*/
t_env		*split_envp(char **envp);
t_env		*ft_list_env(char *key, char *value);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_lstlast_env(t_env *lst);
int			search_map_env(t_env *env, char *str);

/*lst_lexer.c*/
t_lexer		*ft_list(char **argv);
int			ft_check_token(char *str);
t_lexer		*ft_lstnew(char *str, char *token);
void		ft_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer		*ft_lstlast(t_lexer *lst);

/*parser_env*/
char		*get_env_var(char *var_name, t_env *envt);
char		*expand_env_vars(char *input, t_env *env);
char		*check_var_name(char **point, char *temp, t_env *env);
void		parser_env(t_lexer **lexer, t_env *env);
void		string_expander(t_lexer **lexer, t_env *env, int flag, char *str);

/*pipe.c*/
void		split_command(t_lexer **lexer, t_env *env, char **envp);
void 		set_fork(t_lexer **start, t_fd *fd, t_env *env, char **envp);
void		child(t_lexer **start, t_fd *fd, t_env *env, char **envp);
void		last_command(t_lexer **start, t_fd *fd, t_env *env, char **envp);

/*builtin_utils*/
t_lexer		*new_start(t_lexer **lexer);
char		**new_temp(t_lexer *start);
char		**new_full_temp(t_lexer **lexer);
int			check_pipe(t_lexer **lexer);
int			check_redirection(t_lexer **lexer);

/*builtin_utils2*/
t_lexer		*new_start_redirection(t_lexer **lexer);
char		**new_temp_redirection(t_lexer *start);
int			count_lexer(t_lexer **lexer);
void		init_prev(t_lexer **lexer);
char		*copy_var_value(char *write, char *var_value);

/*redirections.c*/
void		manage_redirections(t_lexer **start, t_fd *fd, int process);
int			redirection_out(t_lexer **start, t_fd *fd);
int			redirection_in(t_lexer **start);
int			red_append(t_lexer **start, t_fd *fd);
void		free_fd(t_fd *fd, int fd_in);

/*commands*/
int			builtin_cd(t_lexer **lexer);
int			builtin_pwd(t_lexer **lexer);
int			builtin_echo(t_lexer **lexer);
int			builtin_unset(t_lexer **lexer, t_env *env);
int			unset_env(t_lexer **lexer, t_env *env);

/*builtin_env*/
int			builtin_env(t_lexer **lexer, t_env *env);
t_env		*ft_lstcopy_env(t_env *lst);
int			del_first_env(t_lexer **lexer, t_env *env);
int			del_last_env(t_lexer **lexer, t_env *env);
void		new_node_env(int index, t_env *env, char *temp_value);

/*bultin_export*/
int			builtin_export(t_lexer **lexer, t_env *env);
void		builtin_temp_export(t_lexer **lexer, t_env *env);
void		find_value_env(t_env *env, char *temp_key, char *temp_value);
void		swap_nodes(t_env **head, t_env *prev, t_env *current, t_env *next);
void		bubble_sort_export(t_env **head);

/*execve.c*/
int			command_execve(char **temp, char **envp);
int			execute_command(char *path_env, char *command, char *path, int len);
int			find_command(char *command, char *path);
void		check_echo(t_lexer *lexer);
int			manage_builtin(t_lexer **lexer, t_env *env);

/*heredoc.c*/
void		manage_heredoc(t_lexer **lexer);
void		readline_heredoc(char *str, t_lexer **lexer);
int			redirection_heredoc(t_lexer **start);
char		*ft_strjoin_heredoc(char *s1, char *s2);

/*utils.c*/
char		*ft_strdup(char *str);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strcat(char *dest, char *src);

/*utils2.c*/
int			ft_strlen(char *str);
char		*ft_superlen(int len, int len2);
char		*ft_substr(char *s, unsigned int start, size_t len);
int			get_word(char *s, char c);
char		**ft_split(char *s, char c);

/*utils3.c*/
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
void		check_all(int *single_q, int *double_q, char *s_read, char *s_write);
void		remove_all_quotes(t_lexer **lexer);

/*utils4.c*/
int			ft_len(int n);
char		*ft_minint(int n);
char		*ft_itoa(int n);
int			ft_isalnum(int c);
char		*ft_strcpy(char *dest, char *src);

/*utils5.c*/
int			ft_check_all_quotes(char *str);
int			check_token_error(t_lexer **lexer);

#endif