/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:57:14 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 22:50:57 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../headers/minishell.h"

int	find_flag(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (-1);
	if (ft_strncmp(&cmd[i], "-", 1) == 0 \
	&& ft_strncmp(&cmd[i + 1], "n", 1) == 0)
	{
		i = i + 2;
		while (cmd[i])
		{
			if (ft_strncmp(&cmd[i], "n", 1) != 0)
				return (-1);
			else
				i++;
		}
		return (0);
	}
	return (-1);
}

int	ft_echo(t_ppl **ppl)
{
	int	flag_n;
	int	flag_echo;

	flag_n = 0;
	flag_echo = 0;
	if (!(*ppl)->ppl_cmd)
		return (EXIT_FAILURE);
	if (!(*ppl)->ppl_cmd[1])
	{
		flag_echo = 1;
		(*ppl)->pp_exit = print_and_return(ppl, flag_echo, flag_n);
		my_free((*ppl)->pp_first_cmd);
		my_free((*ppl)->ppl_cmd[0]);
		my_free((*ppl)->ppl_cmd[1]);
		return (EXIT_SUCCESS);
	}
	if (find_flag((*ppl)->ppl_cmd[1]) == 0)
		flag_n = 1;
	(*ppl)->pp_exit = print_and_return(ppl, flag_echo, flag_n);
	my_free((*ppl)->pp_first_cmd);
	my_free((*ppl)->ppl_cmd[0]);
	my_free((*ppl)->ppl_cmd[1]);
	return (EXIT_SUCCESS);
}

// static void	print_echo_n_flag(t_ppl *ppl, int i)
// {
// 	while (ppl->ppl_cmd[i])
// 	{
// 		ft_putstr_fd(ppl->ppl_cmd[i], STDOUT_FILENO);
// 		if (ppl->ppl_cmd[i + 1])
// 			ft_putchar_fd(' ', STDOUT_FILENO);
// 		i++;
// 	}
// }

static void	print_echo_n_flag(t_ppl *ppl, int i)
{
	int	flag_n;

	flag_n = 1;
	while (ppl->ppl_cmd[i] && flag_n)
	{
		if (ft_strncmp(ppl->ppl_cmd[i], "-n", 2) == 0)
			i++;
		else
		{
			flag_n = 0;
		}
	}
	while (ppl->ppl_cmd[i])
	{
		ft_putstr_fd(ppl->ppl_cmd[i], STDOUT_FILENO);
		if (ppl->ppl_cmd[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

static void	print_echo_arg(t_ppl *ppl)
{
	int	i;

	i = 1;
	while (ppl->ppl_cmd[i])
	{
		ft_putstr_fd(ppl->ppl_cmd[i], STDOUT_FILENO);
		if (ppl->ppl_cmd[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	print_and_return(t_ppl **ppl, int flag_echo, int flag_n)
{
	int	i;

	i = 0;
	if (flag_echo == 1)
	{
		g_exit_status = 0;
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	if (flag_n == 1)
	{
		if (!(*ppl)->ppl_cmd[i + 2])
			return (EXIT_SUCCESS);
		else
			print_echo_n_flag(*ppl, i + 2);
	}
	else
		print_echo_arg(*ppl);
	g_exit_status = 0;
	return (EXIT_SUCCESS);
}
