/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:57:21 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/15 21:57:22 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../headers/minishell.h"

int	ft_env(t_ppl **ppl)
{
	t_envnode	*mini_envp;

	mini_envp = (*ppl)->pp_list_env;
	if (!mini_envp)
		return (0);
	print_mini_envp(mini_envp);
	return (EXIT_SUCCESS);
}
