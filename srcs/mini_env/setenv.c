/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:09:17 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 16:09:18 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../headers/minishell.h"

int	ft_setenv(char *name, char *value, char *content, t_envnode **env)
{
	t_envnode	*var;
	t_envnode	*new_var;

	var = find_env_var(name, env);
	if (var)
	{
		my_free(var->value);
		var->value = ft_strdup(value);
		my_free(var->content);
		var->content = ft_strdup(content);
	}
	else
	{
		new_var = create_mini_envvar_node(name, value, content);
		ft_add_envlist(new_var, env);
	}
	return (0);
}

int	home_not_set(char *home, char *pwd)
{
	if (home == NULL || pwd == NULL)
		return (0);
	return (-1);
}
