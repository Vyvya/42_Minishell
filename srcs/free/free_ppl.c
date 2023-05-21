/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ppl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:10:19 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 20:43:08 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_ppl(t_ppl **new_ppl, int *i)
{
	int	j;

	j = 0;
	my_free((*new_ppl)->pp_first_cmd);
	while (j < *i)
	{
		my_free((*new_ppl)->ppl_cmd[j]);
		j++;
	}
	my_free((*new_ppl)->ppl_cmd);
	my_free((*new_ppl));
}

void	free_one_ppl(t_ppl **new_ppl)
{
	my_free((*new_ppl)->pp_first_cmd);
	my_free((*new_ppl)->ppl_cmd[0]);
	my_free((*new_ppl)->ppl_cmd);
	my_free((*new_ppl));
}
