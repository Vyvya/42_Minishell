/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:28:18 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/15 23:28:19 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../headers/minishell.h"

int	ft_unset(t_ppl **ppl)
{
	int		i;
	char	*res;
	t_ppl	*ppl_p;

	i = 1;
	ppl_p = *ppl;
	if (ppl_p->ppl_cmd[i] == NULL)
		return (0);
	while (ppl_p->ppl_cmd[i])
	{
		res = check_if_in_env(&ppl_p->pp_list_env, ppl_p->ppl_cmd[i]);
		if (res != NULL)
		{
			if (!remove_from_list(&ppl_p->pp_list_env, ppl_p->ppl_cmd[i]))
				ft_exit(&ppl_p);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	remove_from_list(t_envnode **mini_env, char *key)
{
	t_envnode	*curr;
	t_envnode	*temp;
	int			len;

	curr = *mini_env;
	len = ft_strlen(key);
	if (delete_first_node(&mini_env, key))
		return (!!*mini_env);
	while (curr && ft_strncmp(curr->key, key, len + 1))
	{
		temp = curr;
		curr = curr->next;
	}
	if (curr && !ft_strncmp(curr->key, key, len + 1))
	{
		temp->next = curr->next;
		my_free(curr->key);
		my_free(curr->value);
		curr->key = NULL;
		curr->value = NULL;
		my_free(curr);
		curr = NULL;
	}
	return (1);
}

int	delete_first_node(t_envnode ***hd, char *key)
{
	t_envnode	*head;

	head = **hd;
	if (head == NULL)
		return (0);
	if (ft_strcmp(head->key, key) == 0)
	{
		head = head->next;
		my_free(head->key);
		head->key = NULL;
		my_free(head->value);
		head->value = NULL;
		my_free(head);
		head = NULL;
		**hd = head;
		return (1);
	}
	return (0);
}

char	*check_if_in_env(t_envnode **mini_env, char *arg)
{
	t_envnode	*curr;
	int			l;

	curr = *mini_env;
	l = ft_strlen(arg);
	while (curr)
	{
		if (ft_strncmp(curr->key, arg, l + 1) == 0)
			return (curr->key);
		curr = curr->next;
	}
	return (NULL);
}
