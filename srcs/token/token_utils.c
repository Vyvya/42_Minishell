#include "../../headers/minishell.h"

void	ft_strdel(char **as)
{
	if (as && *as)
	{
		my_free(*as);
		*as = NULL;
	}
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1 || !s2)
		result = ft_strdup(s1 ? s1 : s2);
	else
	{
		result = (char *)my_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
		if (!result)
			return (NULL);
		ft_strlcpy(result, s1, ft_strlen(s1) + 1);
		ft_strlcat(result, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	}
	ft_strdel(&s1);
	return (result);
}

size_t	ft_strcspn(const char *str, const char *charset)
{
	const char *p;
	const char *q;
	size_t count;

	p = str;
	count = 0;
	while (*p != '\0')
	{
		q = charset;
		while (*q != '\0')
		{
			if (*p == *q)
				return (count);
			q++;
		}
		p++;
		count++;
	}
	return (count);
}

int	ft_bool_strcspn(const char *str, const char *charset)
{
	const char *p;
	const char *q;

	p = str;
	while (*p != '\0')
	{
		q = charset;
		while (*q != '\0')
		{
			if (*p == *q)
				return (1);
			q++;
		}
		p++;
	}
	return (0);
}

int	ft_strset(const char *s1, char *s2)
{
	printf("s1 %s\n", s1);
	printf("s2 %s\n", s2);
	if (!s1 || !s2)
	{
		printf("no s1 || s2\n");
		return (-1);
	}
	while (s1 && s2)
	{
		printf("*s1 %c\n", *s1);
		printf("*s2 %c\n", *s2);
		if (ft_strchr(s1, (int)(*s2)))
		{
			printf("*s1 %c\n", *s1);
			printf("*s2 %c\n", *s2);
			return (1);
		}
		s2++;
	}
	return (0);
}

// static void	*expand_token_list_sub(t_token *curr, t_envnode *mini_env, \
// char *expanded, char *d_trimmed)
// {
// 	if (curr->id == TOK_D_QUOTE)
// 	{
// 		d_trimmed = ft_strtrim(curr->content, "\"");
// 		my_free(curr->content);
// 		curr->content = d_trimmed;
// 		curr->id = TOK_D_QUOTE;
// 	}
// 	if (ft_strncmp(curr->content, "$?", 2) != 0)
// 	{
// 		expanded = expand_token(&curr->content, mini_env);
// 		if (expanded == NULL)
// 			return (NULL);
// 		my_free(curr->content);
// 		curr->content = ft_strdup(expanded);
// 		my_free(expanded);
// 	}
// 	if (expanded == NULL)
// 		return (NULL);
// 	return (curr);
// }

// void	*expand_token_list(t_token **token_head, t_envnode *mini_env)
// {
// 	t_token	*curr;
// 	char	*expanded;
// 	char	*d_trimmed;
// 	char	*s_trimmed;

// 	curr = *token_head;
// 	expanded = NULL;
// 	d_trimmed = NULL;
// 	s_trimmed = NULL;
// 	while (curr != NULL)
// 	{
// 		if (curr->id == TOK_WORD || curr->id == TOK_D_QUOTE)
// 			curr = expand_token_list_sub(curr, mini_env, expanded, d_trimmed);
// 		if (curr->id == TOK_S_QUOTE)
// 		{
// 			s_trimmed = ft_strtrim(curr->content, "\'");
// 			my_free(curr->content);
// 			curr->content = ft_strdup(s_trimmed);
// 			my_free(s_trimmed);
// 			curr->id = TOK_WORD;
// 		}
// 		curr = curr->next;
// 	}
// 	return (*token_head);
// }