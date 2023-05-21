/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_find.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:59:21 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 17:30:07 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*find_path(char **mini_env_array)
{
	while (*mini_env_array && ft_strncmp("PATH", *mini_env_array, 4))
		mini_env_array++;
	return (*mini_env_array + 5);
}

static char	*get_curr_dir(void)
{
	char	*cwd;

	cwd = (char *)my_malloc(PATH_MAX * sizeof(char));
	if (cwd != NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			cwd = NULL;
		}
	}
	return (cwd);
}

int	find_curr_dir(char **path)
{
	char	*curr_dir;

	curr_dir = NULL;
	curr_dir = get_curr_dir();
	if (curr_dir != NULL)
	{
		*path = (char *)my_malloc((strlen(curr_dir) + \
		ft_strlen("/minishell") + 1) * sizeof(char));
		if (*path != NULL)
		{
			ft_strlcpy(*path, curr_dir, (strlen(curr_dir) + 1));
			*path = ft_strjoin(*path, "/minishell");
		}
	}
	return (0);
}

int	check_path_var(t_ppl **ppl_p)
{
	t_ppl	*ppl;
	char	*path_var;

	ppl = *ppl_p;
	path_var = "PATH";
	while (*ppl->pp_arr_env != NULL)
	{
		if (!ft_equals_str(path_var, *ppl->pp_arr_env))
			return (1);
		ppl->pp_arr_env++;
	}
	if (ppl->pp_arr_env == NULL)
		error_path_cmd(ppl);
	return (0);
}
