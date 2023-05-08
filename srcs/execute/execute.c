#include "../../headers/minishell.h"

void execute(t_cmd *cmd, int cmd_num, t_envnode *mini_env)
{
	t_ppline	*ppline;

	// print_cmd_list(cmd);
	ppline = build_ppline_array(&cmd, cmd_num, mini_env);

	ter_attr_handler_off();
	signals_default();
	if (ppline->ppline_idx == 1 && ppline->pp_red_status == 0 && check_if_builtin(ppline->pp_first_cmd) == 0)
	{
		ppline->pp_exit = execute_builtin(&ppline);
		g_exit_status = ppline->pp_exit;
		return ;
	}
	// if (ft_strcmp("minishell", ppline->pp_first_cmd) == 0)
	// {
	// 	pid_t child_pid = fork();
	// 	if (child_pid == 0)
	// 	{
	// 		// Child process
	// 		execute(cmd, cmd_num, mini_env);
	// 		exit(EXIT_SUCCESS);
	// 	}
	// 	else if (child_pid > 0)
	// 	{
	// 		// Parent process
	// 		wait(NULL); // Wait for the child process to finish
	// 	}
	// 	else
	// 	{
	// 		// Fork failed
	// 		perror("fork");
	// 		// Handle the error
	// 	}
	// }
	else
		ppline->pp_exit = execute_multi_cmd(ppline);
	signal_at_beginning();
	ter_attr_handler_on();
}
