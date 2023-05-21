/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:00:04 by vgejno            #+#    #+#             */
/*   Updated: 2023/05/16 17:53:59 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	search_path_array(t_ppl *ppl, char **cmd_path)
{
	char	**path_array;
	char	*temp;
	int		i;

	i = 0;
	path_array = ft_split(*cmd_path, ':');
	while (path_array[i])
	{
		temp = ft_strjoin(path_array[i], "/");
		*cmd_path = ft_strjoin(temp, ppl->ppl_cmd[0]);
		if (!access(*cmd_path, F_OK))
			return (-1);
		i++;
	}
	return (0);
}

static int	check_curr_dir(t_ppl *ppl, char **cmd_path, \
char *instance, char **mini_path)
{
	if (ft_strncmp(instance, ppl->pp_first_cmd, ft_strlen(instance)) == 0)
	{
		if (find_curr_dir(mini_path) == 0)
		{
			*cmd_path = ft_strdup(*mini_path);
			if (!access(*cmd_path, F_OK) && !access(*cmd_path, X_OK))
				return (-1);
		}
		return (0);
	}
	return (0);
}

int	ft_equals_str(const char *str1, const char *str2)
{
	size_t	length;

	length = ft_strlen(str1);
	if (ft_strlen(str2) < length || str2[length] != '=')
		return (1);
	return (ft_strncmp(str1, str2, length));
}

static int	manage_bin_path(t_ppl **ppl_p, char **cmd_path)
{
	t_ppl	*ppl;

	ppl = *ppl_p;
	if (access(ppl->pp_first_cmd, F_OK) == 0)
	{
		*cmd_path = ft_strdup(ppl->pp_first_cmd);
		return (1);
	}
	else
	{
		error_path_cmd(ppl);
		return (-1);
	}
}

int	search_path(t_ppl *ppl, char **cmd_path)
{
	char	*instance;
	char	*mini_path;

	instance = "./minishell";
	mini_path = NULL;
	if (ft_strchr(ppl->pp_first_cmd, '/') != NULL)
	{
		if (manage_bin_path(&ppl, cmd_path))
			return (1);
		return (-1);
	}
	else if (check_curr_dir(ppl, cmd_path, instance, &mini_path) == -1)
		return (-1);
	if (check_path_var(&ppl) == 0)
		error_path_cmd(ppl);
	*cmd_path = find_path(ppl->pp_arr_env);
	if (*cmd_path == NULL)
		error_path_cmd(ppl);
	if (search_path_array(ppl, cmd_path) == -1)
		return (-1);
	return (0);
}
