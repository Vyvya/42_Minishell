#include "../../headers/minishell.h"

static char	*mini_getenv(char *var_name, int var_len, t_envnode *mini_env)
{
	t_envnode	*temp;
	char		*empty;

	temp = mini_env;
	empty = "";
	while (temp)
	{
		if (ft_strncmp(var_name, temp->key, var_len) \
		== 0 && (int)ft_strlen(temp->key) == var_len)
			return (temp->value);
		temp = temp->next;
	}
	return (empty);
}

static char	*expand_token_sub(char **content, char *prefix, \
char *expanded, char *var_value)
{
	expanded = ft_strjoin_free(expanded, prefix);
	expanded = ft_strjoin_free(expanded, var_value);
	*content = *content + ft_strcspn(*content + 1, " $;|/\'&><\n") + 1;
	ft_strdel(&prefix);
	if (*content == *content - 1)
		expanded = ft_strjoin_free(expanded, "$");
	return (expanded);
}

static char	*find_var_value(char **content, t_envnode *mini_env, \
char *var_name, char *var_value)
{
	var_value = mini_getenv(var_name, \
	ft_strcspn(*content + 1, " $;|/\'&><\n"), mini_env);
	if (!var_value)
		var_value = "";
	ft_strdel(&var_name);
	return (var_value);
}

char	*expand_token(char **content, t_envnode *mini_env)
{
	char	*p;
	char	*var_name;
	char	*prefix;
	char	*expanded;
	char	*var_value;

	p = *content;
	prefix = NULL;
	expanded = NULL;
	var_value = NULL;
	while (p && *p)
	{
		if (*p == '$' && p[1])
		{
			prefix = ft_substr(*content, 0, p - *content);
			var_name = ft_substr(p + 1, 0, ft_strcspn(p + 1, " $;|/\'&><\n"));
			var_value = find_var_value(content, mini_env, var_name, var_value);
			expanded = expand_token_sub(content, prefix, expanded, var_value);
			p = *content;
		}
		else
			p++;
	}
	return (ft_strjoin_free(expanded, *content));
}
