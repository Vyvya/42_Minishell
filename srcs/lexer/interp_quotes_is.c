/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interp_quotes_is.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:09:33 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 16:09:34 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_q(char c)
{
	if (c == '\'' || c == '"')
	{
		return (1);
	}
	return (0);
}

// eval_quote
int	eqt(char *q)
{
	if (*q == '\"')
		return (T_DQ);
	else if (*q == '\'')
		return (T_SQ);
	return (0);
}
