/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:07:34 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 22:08:20 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	*manage_trim(t_token **curr, char *d_trim)
{
	d_trim = ft_strtrim((*curr)->content, "\"");
	my_free((*curr)->content);
	(*curr)->content = d_trim;
	(*curr)->id = T_DQ;
	return (0);
}

static void	*manage_dollarwhat(char **content)
{
	char	*temp;

	temp = ft_itoa(g_exit_status);
	free(*content);
	*content = NULL;
	*content = ft_strdup(temp);
	free(temp);
	temp = NULL;
	return (0);
}

static void	*exp_toklist_s(t_token *curr, t_envnode *mini_env, \
char *exp, char *d_trim)
{
	int		len;

	len = ft_strlen(curr->content);
	if (len == 0)
		return (0);
	if (curr->id == T_DQ)
		manage_trim(&curr, d_trim);
	if (curr->content && len >= 2 && ft_strncmp(curr->content, "$?", 2) == 0)
		manage_dollarwhat(&curr->content);
	if (curr->content && ft_strncmp(curr->content, "$?", 2) != 0)
	{
		exp = exp_tok(&curr->content, mini_env);
		if (exp == NULL)
			return (NULL);
		my_free(curr->content);
		curr->content = ft_strdup(exp);
		my_free(exp);
	}
	if (ft_strncmp(curr->content, "$?", 2) != 0 && exp == NULL)
		return (NULL);
	return (curr);
}

void	*exp_toklist(t_token **token_head, t_envnode *mini_env)
{
	t_token	*curr;
	char	*exp;
	char	*d_trim;
	char	*s_trim;

	curr = *token_head;
	exp = NULL;
	d_trim = NULL;
	s_trim = NULL;
	while (curr != NULL)
	{
		if (curr->id == T_W || curr->id == T_DQ)
			curr = exp_toklist_s(curr, mini_env, exp, d_trim);
		if (curr->id == T_SQ)
		{
			s_trim = ft_strtrim(curr->content, "\'");
			my_free(curr->content);
			curr->content = ft_strdup(s_trim);
			my_free(s_trim);
			curr->id = T_W;
		}
		curr = curr->next;
	}
	return (*token_head);
}
