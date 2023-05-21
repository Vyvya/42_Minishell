/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppl_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:10:44 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 16:10:45 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	append_ppl(t_ppl **ppl, t_ppl *new_ppl, \
t_ppl **ppl_tail)
{
	if (*ppl == NULL)
	{
		*ppl = new_ppl;
		*ppl_tail = new_ppl;
	}
	else
	{
		(*ppl_tail)->next = new_ppl;
		*ppl_tail = new_ppl;
	}
}

static void	fill_env_ppl(t_ppl *ppl, t_envnode *mini_env, int pp_idx)
{
	ppl->pp_arr_env = mini_env_arr(mini_env, mini_env_size(mini_env));
	ppl->pp_list_env = mini_env;
	ppl->ppl_idx = pp_idx;
}

static int	handle_redir(t_ppl *new_ppl, t_token *cmd_red)
{
	int	res;

	res = ft_handle_red_all(&new_ppl, cmd_red);
	if (res == 1)
	{
		new_ppl->pp_red_status = 1;
		return (1);
	}
	else if (res == 2)
	{
		g_exit_status = 1;
		ft_putstr_fd("minishell_VH: ", STDERR_FILENO);
		ft_putstr_fd(cmd_red->next->content, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (0);
	}
	return (0);
}

static int	handle_cmd_word_red(t_ppl **p_ppl, t_cmd **cmd_ptr_head)
{
	t_ppl	*new_ppl;
	t_cmd	*cmd_ptr;

	new_ppl = *p_ppl;
	cmd_ptr = *cmd_ptr_head;
	if (cmd_ptr->cmd_word)
		handle_word(&new_ppl, cmd_ptr->cmd_word);
	if (cmd_ptr->cmd_red)
	{
		if (!handle_redir(new_ppl, cmd_ptr->cmd_red))
			return (0);
	}
	return (1);
}

t_ppl	*build_ppl(t_cmd **cmd_head, int cmd_n, t_envnode *mini_env)
{
	t_ppl	*ppl;
	t_ppl	*new_ppl;
	t_ppl	*ppl_tail;
	int		pp_idx;

	pp_idx = cmd_n;
	ppl = NULL;
	new_ppl = NULL;
	ppl_tail = NULL;
	while ((*cmd_head) != NULL && cmd_n-- > -1)
	{
		new_ppl = ft_new_ppl();
		if (new_ppl == NULL)
			return (NULL);
		fill_env_ppl(new_ppl, mini_env, pp_idx);
		if ((*cmd_head)->cmd_word || (*cmd_head)->cmd_red)
		{
			if (!handle_cmd_word_red(&new_ppl, &(*cmd_head)))
				return (NULL);
		}
		append_ppl(&ppl, new_ppl, &ppl_tail);
		(*cmd_head) = (*cmd_head)->next;
	}
	return (ppl);
}
