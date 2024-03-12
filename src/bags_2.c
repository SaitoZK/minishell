#include "../inc/minishell.h"

char	*heredoc(t_tokens **token)
{
	char	*line;
	char	*doc;

	doc = ft_strdup("");
	while (1)
	{
		line = readline("");
		if (!(ft_strncmp((*token)->token, line, ft_strlen((*token)->token)))
			&& !(ft_strncmp((*token)->token, line, ft_strlen(line))))
		{
			free (line);
			break ;
		}
		if (doc[0] != '\0')
			doc = ft_strjoin(doc, "\n");
		doc = ft_strjoin(doc, line);
		free(line);
	}
	return (doc);
}

int	chev_utils(t_cmd **cmd_st, t_tokens **token, int a)
{
	(*cmd_st)->append = a;
	*token = (*token)->next;
	if ((*cmd_st)->append == 0)
	{
		if (access((*token)->token, F_OK) == 0
			&& access((*token)->token, W_OK) == -1)
		{
			printf("Error accessing file\n");
			return (-1);
		}
		open((*token)->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if ((*cmd_st)->append == 1)
	{
		if (access((*token)->token, F_OK) == 0
			&& access((*token)->token, W_OK) == -1)
		{
			printf("Error accessing file\n");
			return (-1);
		}
		open((*token)->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	(*cmd_st)->outfile = (*token)->token;
	return (1);
}

int	chev_utils_bis(t_cmd **cmd_st, t_tokens **token, int a)
{
	if (a == 1)
	{
		*token = (*token)->next;
		(*cmd_st)->heredoc = heredoc(token);
		(*cmd_st)->doc = a;
	}
	if (a == 0)
	{
		*token = (*token)->next;
		(*cmd_st)->infile = (*token)->token;
		if (access((*token)->token, F_OK) == -1)
		{
			printf("No such file or directory\n");
			return (-1);
		}
		(*cmd_st)->doc = a;
	}
	return (1);
}

int	store_chevron(t_cmd **cmd_st, t_tokens **token)
{
	if (ft_strncmp((*token)->token, "<<", 2) == 0)
	{
		return (chev_utils_bis(cmd_st, token, 1));
	}
	else if (ft_strncmp((*token)->token, "<", 1) == 0)
	{
		return (chev_utils_bis(cmd_st, token, 0));
	}
	else if (ft_strncmp((*token)->token, ">>", 2) == 0)
	{
		return (chev_utils(cmd_st, token, 1));
	}
	else if (ft_strncmp((*token)->token, ">", 1) == 0)
	{
		return (chev_utils(cmd_st, token, 0));
	}
	return (0);
}

void	fill_cmd_st(t_cmd *new_cmd, t_tokens *current_token, char **path)
{
	int	cmd_found;
	int	is_chevron;

	cmd_found = 0;
	is_chevron = 0;
	while (current_token)
	{
		is_chevron = store_chevron(&new_cmd, &current_token);
		if (is_chevron == -1)
		{
			new_cmd->error = 1;
			break ;
		}
		if (cmd_found && !is_chevron)
		{
			add_arg(new_cmd, current_token->token);
		}
		if (!new_cmd->cmd && !is_chevron)
			cmd_found = add_cmd_and_type(current_token, new_cmd, path);
		current_token = current_token->next;
	}
}