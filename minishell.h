/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:27:09 by nfurlani          #+#    #+#             */
/*   Updated: 2024/03/13 18:26:40 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_lexer
{
	char			*str;
	int				index;
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

/*main.c*/
int			ft_exit(char *str);
void		reading(t_env **env);

/*parser*/
void		parser(char *str, t_env **env);
void		manage_string(t_lexer **lexer);
void		join_string(t_lexer *lexer);
void		lexer_index(t_lexer **lexer);
void		manage_token(t_lexer **lexer);
void		print_lexer(t_lexer **lexer);

/*quotes.c*/
void		find_quotes(char **temp);
int			count_quotes(char *str, char c);
void		remove_char(char *str, char c, int count);
void		manage_quote(char **temp, char c);
void		single_quote(char **temp);

/*parser_token.c*/
void		init_prev(t_lexer **lexer);
int			check_character(char c);
void		manage_token(t_lexer **lexer);
t_lexer		*new_token(char **array);
t_lexer		*new_list(t_lexer *current, t_lexer **new);

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

/*lst_lexer.c*/
t_lexer		*ft_list(int argc, char **argv);
int			ft_check_token(char *str);
t_lexer		*ft_lstnew(char *str, char *token);
void		ft_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer		*ft_lstlast(t_lexer *lst);

/*parser_env*/
void		parser_env(t_lexer **lexer, t_env **env);
int			search_map(t_env **env, char *str);

/*utils.c*/
char		*ft_strdup(char *str);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strchr(const char *s, int c);

/*utils2.c*/
int			ft_strlen(char *str);
char		*ft_superlen(int len, int len2);
char		*ft_substr(char *s, unsigned int start, size_t len);
int			get_word(char *s, char c);
char		**ft_split(char *s, char c);

/*utils4.c*/
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);

#endif