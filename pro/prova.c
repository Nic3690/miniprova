# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_lexer
{
	char			*str;
	int				index;
	struct s_lexer	*next;
}	t_lexer;

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		n;
	int		len1;
	int		len2;

	i = -1;
	n = 0;
	len1 = 0;
	len2 = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[len1] != '\0')
		len1++;
	while (s2[len2] != '\0')
		len2++;
	str = malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[n] != '\0')
		str[i++] = s2[n++];
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (0);
}

int	count_quotes(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	join_string(t_lexer *lexer)
{
	t_lexer	*temp;

	lexer->str = ft_strjoin(lexer->str, lexer->next->str);	
	temp = lexer->next->next;
	free(lexer->next);
	lexer->next = temp;
}

/*Nella funzione manage_string(), quando unisci due stringhe e liberi il nodo successivo, non stai controllando se temp (ovvero lexer->next->next) è NULL prima di assegnare la sua str a lexer->str. Se temp è NULL, stai tentando di accedere a un membro di una struttura che non esiste.*/

void	manage_string(t_lexer **lexer)
{
	while (*lexer && (*lexer)->next)
	{
		if (ft_strchr((*lexer)->str, '"'))
			join_string(*lexer);
		if (count_quotes((*lexer)->str, '"') == 2 && (*lexer)->next != 0)
			*lexer = (*lexer)->next;
	}
}

void	lexer_index(t_lexer **lexer)
{
	while (*lexer && (*lexer)->next)
	{
		if (ft_strchr ((*lexer)->str, ' '))
			(*lexer)->index += 1;
		if ((*lexer)->next == NULL)
            break;
		(*lexer) = (*lexer)->next;
	}
}

int main()
{
	t_lexer **lexer = malloc(sizeof(t_lexer **) * 10000);
	*lexer = malloc(sizeof(t_lexer *));
	(*lexer)->next = malloc(sizeof(t_lexer *));
	(*lexer)->next->next = malloc(sizeof(t_lexer *));
	(*lexer)->str = "\"ciao";
	(*lexer)->next->str = "come";
	(*lexer)->next->next->str = "va\"";
	(*lexer)->index = 0;
	manage_string(lexer);
	lexer_index(lexer);
	printf("%s\n", (*lexer)->str);
	printf("%d\n", (*lexer)->index);
}