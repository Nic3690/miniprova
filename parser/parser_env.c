/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:16:00 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/16 16:03:33 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_var(char *var_name, t_env *env)
{
	t_env		*current;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(g_exit_code));
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return (getenv(var_name));
}

char	*expand_env_vars(char *input, t_env *env)
{
	char	*result;
	char	*point;
	char	*temp;
	
	result = ft_calloc(1024, sizeof(char));
	if (!result)
		return (NULL);
	point = input;
	temp = result;
	while (*point)
	{
		if (*point == '$')
			temp = check_var_name(&point, temp, env);
		else
			*temp++ = *point;
		point++;
	}
	*temp = '\0';
	return (result);
}

char	*check_var_name(char **point, char *temp, t_env *env)
{
	char	*var_start;
	char	var_name[100];
	char	*var_value;
	int		var_len;

	(*point)++;
	var_start = *point;
	while (**point && (ft_isalnum(**point) || **point == '_' || **point == '?'))
		(*point)++;
	var_len = *point - var_start;
	ft_strncpy(var_name, var_start, var_len);
	var_name[var_len] = '\0';
	var_value = get_env_var(var_name, env);
	if (var_value)
	{
		while (*var_value)
			*temp++ = *var_value++;
	}
	(*point)--;
	return (temp);
}

void	parser_env(t_lexer **lexer, t_env *env)
{
	t_lexer	*head_lexer;
	char	*str;
	int		flag;

	head_lexer = *lexer;
	flag = 1;
	while (*lexer)
	{
		str = (*lexer)->str;
		flag = 1;
		string_expander(lexer, env, flag, str);
		*lexer = (*lexer)->next;
	}
	*lexer = head_lexer;
}

void	string_expander(t_lexer **lexer, t_env *env, int flag, char *str)
{
	int		i;
	char	*expanded_str;

	i = 0;
	if (!str)
		return ;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			flag = !flag;
		else if (str[i] == '$' && flag)
		{
			expanded_str = expand_env_vars(str, env);
			if (expanded_str)
			{
				free((*lexer)->str);
				(*lexer)->str = expanded_str;
				break ;
			}
		}
		i++;
	}
}
