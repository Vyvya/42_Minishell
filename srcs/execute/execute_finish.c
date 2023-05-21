/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_finish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:15:09 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/15 23:15:10 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	finish_exec(t_ppl **p_ppl)
{
	t_ppl	*ppl;

	ppl = *p_ppl;
	close_red_fds(&ppl);
	close_fds(&ppl);
}

void	finish_multi_exec(t_ppl **p_ppl)
{
	t_ppl	*ppl;

	ppl = *p_ppl;
	execute_parent(&ppl);
	close(STDOUT_FILENO);
	close_fds(&ppl);
	dup2_saved_stds(&ppl);
	close_saved_stds(&ppl);
}
