
typedef struct s_cmd
{
	pid_t				process_id;
	char				*content;
	int					redir_out;
	int					redir_in;
	struct s_cmd		*next;
}	t_cmd;

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->content = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_word	*init_word(char *content, int id)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (0);
	word->content = content;
	word->id = id;
	word->next = NULL;
	return (word);
}

t_blank	*white_space(char *content, int id)
{
	t_blank	*space;

	space = malloc(sizeof(t_blank));
	if (!space)
		return (0);
	space->content = content;
	space->id = id;
	space->next = NULL;
	return (space);
}

t_arg	*args(char *content, int id)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (0);
	arg->content = content;
	arg->id = id;
	arg->next = NULL;
	return (arg);
}