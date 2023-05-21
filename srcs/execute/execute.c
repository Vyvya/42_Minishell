/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:13:41 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 17:55:59 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	*manage_finish_hdoc(t_ppl **ppl)
{
	dup2((*ppl)->saved_stdin, STDIN_FILENO);
	close((*ppl)->saved_stdin);
	return (0);
}

static void	*check_heredoc(t_ppl **ppl_p)
{
	t_ppl	*ppl;

	ppl = *ppl_p;
	if ((ppl)->pp_heredoc_status == 1)
		execute_heredoc(&ppl);
	return (0);
}

int	execute_pipe_cmd(t_ppl *ppl)
{
	int		i;
	t_ppl	*first;

	i = 0;
	first = ppl;
	dup_saved_stds(&ppl);
	init_pipe(&ppl, ppl->ppl_idx);
	while (ppl != NULL && i < ppl->ppl_idx)
	{
		if (ppl->pp_infile < 0 || ppl->pp_outfile < 0)
		{
			ppl = ppl->next;
			continue ;
		}
		check_heredoc(&ppl);
		if (execute_fork_cmd(ppl))
			msg_error("minishell_VH: error executing command", errno);
		if (ppl->pp_heredoc_status == 1)
			manage_finish_hdoc(&ppl);
		ppl = ppl->next;
		i++;
	}
	ppl = first;
	finish_multi_exec(&ppl);
	return (EXIT_SUCCESS);
}

void	execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppl	*ppl;

	ppl = build_ppl(&cmd, cmd_num, mini_env);
	if (ppl == NULL)
		return ;
	my_free(cmd);
	ter_attr_handler_off();
	if (ppl->ppl_idx == 1 && ppl->pp_red_status == 0 && \
	check_if_builtin(ppl->pp_first_cmd) == 0)
	{
		if (execute_to_builtin(ppl))
			msg_error("error executing builtin: ", errno);
	}
	else
	{
		if (execute_pipe_cmd(ppl))
			msg_error("error executing multi_cmd: ", errno);
	}
	signal_at_beginning();
	ter_attr_handler_on();
}
