#include "../inc/minishell.h"

void	free_str(char **str)
{
	if (str && *str)
	{
		free(*str);
		(*str) = NULL;
	}
}

void	clean_list_bag(t_list *list_bag)
{
	t_list	*tmp;
	t_list	*token_list;
	t_list	*tmp_token_list;
	char	*token;

	tmp = NULL;
	if (!list_bag)
		return ;
	while (list_bag)
	{
		token_list = (t_list *)(list_bag->content);
		while (token_list)
		{
			token = (char *)token_list->content;
			free(token);
			token = NULL;
			tmp_token_list = token_list;
			token_list = token_list->next;
			free(tmp_token_list);
			tmp_token_list = NULL;
		}
		tmp = list_bag->next;
		free (list_bag);
		list_bag = tmp;
	}
}

void	clean_list_arg(t_list_arg *args)
{
	t_list_arg	*tmp;

	tmp = NULL;
	if (!args)
		return ;
	while (args)
	{
		free(args->arg);
		tmp = args->next;
		free (args);
		args = tmp;
	}
}

void	clean_cmd_str(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->a_arg && cmd->a_arg[i])
	{
		free(cmd->a_arg[i]);
		i++;
	}
	if (cmd->a_arg)
	{
		free(cmd->a_arg);
		cmd->a_arg = NULL;
	}
	DEBUG
	free_str(&cmd->cmd);
	DEBUG
	clean_list_arg(cmd->args);
	DEBUG
	free_str(&cmd->heredoc);
	DEBUG
	free_str(&cmd->infile);
	DEBUG
	free_str(&cmd->outfile);
	DEBUG
}

void	clean_list_cmd(t_list_cmd *list_cmd)
{
	t_list_cmd	*tmp;

	tmp = NULL;
	if (!list_cmd)
		return ;
	while (list_cmd)
	{
		DEBUG
		clean_cmd_str(list_cmd->cmd);
		DEBUG
		free(list_cmd->cmd);
		DEBUG
		tmp = list_cmd->next;
		free(list_cmd);
		list_cmd = tmp;
	}
}
