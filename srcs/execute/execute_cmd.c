#include "../../headers/minishell.h"

static int	execute_single_red(t_ppline *ppline, char *cmd_path) //
{
	// char	*cmd_path;
	// // int		exit_code;

	// cmd_path = NULL;
	// (void)ppline;
	printf(GGREEN "Execution single_red\n" RS);
	printf("CMD: %s\n", (ppline)->pp_first_cmd);
	// if //(red_ptr->id == TOK_REDIR_OUT)

	if (ft_builtin(ppline->pp_first_cmd))
	{
		printf("Builtin\n");
		// if ()
		dup2((ppline)->pp_outfile, STDOUT_FILENO);
		close((ppline)->pp_outfile);
		is_builtin(&ppline->ppline_cmd[0], ppline->pp_list_env);
		// dup2((ppline)->pp_outfile, STDOUT_FILENO);
		// close((ppline)->pp_outfile);
	}
	else
	{
		printf("NOT builtin\n");
		if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
		{
			printf("NO PATH\n");
			return (-1);
		}
		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
		printf("PP_outfile: %d\n", (ppline)->pp_outfile);
		dup2((ppline)->pp_outfile, STDOUT_FILENO);
		close((ppline)->pp_outfile);
		execve(cmd_path, (ppline)->ppline_cmd, (ppline)->pp_arr_env);
		perror("Juliette erreur");
		exit(-1); //EXIT_FAILURE
	}
	return (0);
}

int	execute_single_cmd(t_ppline *ppline) //, char **mini_env_arr, char **cmd_path
{
	char	*cmd_path;
	// int		exit_code;

	cmd_path = NULL;
	// exit_code = 0;
	printf(PURPLE "Execution single_cmd\n" RS);
	printf(PURPLE "Execution single_cmd pp_red_status: %d\n" RS, ppline->pp_red_status);
	if (ppline->pp_red_status == 0)
	{
		if (is_builtin(&ppline->ppline_cmd[0], ppline->pp_list_env) == -1) //ppline->ppline_env
		{
			printf("NOT builtin\n");
			if (!(search_path(ppline, &cmd_path))) //, mini_env_arr //
			{
				printf("NO PATH\n");
				return (-1);
			}
			printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
			// execute_one_cmd(ppline, mini_env_arr, &cmd_path);
			// execute_cmd(ppline, mini_env_arr); //return (execute_cmd(mini, &cmd, mini_env));
			execute_single_red(ppline, cmd_path);
		}

	}
	else if (ppline->pp_red_status == 1)
		execute_single_red(ppline, cmd_path);
	else
		execute_multi_cmd(ppline);
	// else if (execve(cmd_path, ppline->ppline_cmd, ppline->pp_arr_env) == -1)
	// 	msg_error(ft_strjoin(ppline->ppline_cmd[0], " : command not found\n"), 127);
	return (0);
}

int	execute_multi_cmd(t_ppline *ppline) //, char **mini_env_arr
{
	char		*cmd_path;

	cmd_path = NULL;
	// (void)ppline;
	// (void)mini_env_array;
	printf(GGREEN "Execution of several cmds\n" RS);
	if (ppline->pp_first_cmd && ppline->ppline_idx == 1 && ppline->pp_red_status == 0) //&& !ppline->ppline_cmd[1])
	{
		// if (is_builtin(&ppline->ppline_cmd[0], mini_env) == -1) //ppline->ppline_env
		// {
		// 	printf("NOT builtin\n");
			if (!(search_path(ppline, &cmd_path))) //, mini_env_arr
			{
				printf("NO PATH\n");
				return (-1);
			}
			printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
			// execute_single_cmd(ppline); //, mini_env_arr, &cmd_path
		// }
		return (0);
	}
	return (0);
}

// if (is_builtin(&ppline->ppline_cmd[0], mini_env) == -1) //ppline->ppline_env
	// 	{
	// 		printf("NOT builtin\n");
	// 		if (!(search_path(ppline, mini_env_arr, &cmd_path)))
	// 		{
	// 			printf("NO PATH\n");
	// 			return (-1);
	// 		}
	// 		printf(PURPLE "cmd_path: %s\n" RS, cmd_path);
	// 		// execute_one_cmd(ppline, mini_env_arr, &cmd_path);
	// 		execute_cmd(ppline, mini_env_arr); //return (execute_cmd(mini, &cmd, mini_env));
	// 	}