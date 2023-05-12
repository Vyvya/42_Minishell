#include "../../headers/minishell.h"

static void	*expand_token_list_sub(t_token *curr, t_envnode *mini_env, \
char *expanded, char *d_trimmed)
{
	if (curr->id == TOK_D_QUOTE)
	{
		d_trimmed = ft_strtrim(curr->content, "\"");
		my_free(curr->content);
		curr->content = d_trimmed;
		curr->id = TOK_D_QUOTE;
	}
	if (ft_strncmp(curr->content, "$?", 2) != 0)
	{
		expanded = expand_token(&curr->content, mini_env);
		if (expanded == NULL)
			return (NULL);
		my_free(curr->content);
		curr->content = ft_strdup(expanded);
		my_free(expanded);
	}
	if (expanded == NULL)
		return (NULL);
	return (curr);
}

void	*expand_token_list(t_token **token_head, t_envnode *mini_env)
{
	t_token	*curr;
	char	*expanded;
	char	*d_trimmed;
	char	*s_trimmed;

	curr = *token_head;
	expanded = NULL;
	d_trimmed = NULL;
	s_trimmed = NULL;
	while (curr != NULL)
	{
		if (curr->id == TOK_WORD || curr->id == TOK_D_QUOTE)
			curr = expand_token_list_sub(curr, mini_env, expanded, d_trimmed);
		if (curr->id == TOK_S_QUOTE)
		{
			s_trimmed = ft_strtrim(curr->content, "\'");
			my_free(curr->content);
			curr->content = ft_strdup(s_trimmed);
			my_free(s_trimmed);
			curr->id = TOK_WORD;
		}
		curr = curr->next;
	}
	return (*token_head);
}
