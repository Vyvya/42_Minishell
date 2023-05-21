/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:57:37 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/21 22:24:07 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../headers/minishell.h"

static void	*err_num_exit(t_ppl **ppl)
{
	char	*msg;

	msg = NULL;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	msg = ft_strjoin("minishell_VH: exit: ", (*ppl)->ppl_cmd[1]);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	destroy_all();
	exit (255);
}

static void	*easy_exit(void)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	destroy_all();
	exit (g_exit_status);
}

static void	*too_many_exit(void)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell_VH: exit: too many arguments\n", STDERR_FILENO);
	destroy_all();
	exit (1);
}

static void	*num_exit(t_ppl **ppl)
{
	int		res;

	res = 0;
	res = ft_atoi((*ppl)->ppl_cmd[1]);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	destroy_all();
	exit (res);
}

int	ft_exit(t_ppl **ppl)
{
	int		i;
	t_ppl	*ppl_t;

	i = 0;
	ppl_t = *ppl;
	if ((*ppl)->ppl_cmd[1] != NULL)
	{
		while ((*ppl)->ppl_cmd[1][i] && !ft_isalpha((*ppl)->ppl_cmd[1][i]))
			i++;
		if ((*ppl)->ppl_cmd[1][i] == '\0')
		{
			if ((*ppl)->ppl_cmd[2] == NULL)
				num_exit(&ppl_t);
			else
				too_many_exit();
		}
		else
			err_num_exit(&ppl_t);
	}
	else
		easy_exit();
	return (0);
}
