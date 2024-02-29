#include "../inc/minishell.h"

// Finds an executable file from the command and adds path if necessary
// Returns NULL if not found or no access
char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp_cmd;
	char	*tmp_path;
	int		index;

	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	index = 0;
	while (paths[index])
	{
		tmp_path = ft_strjoin(paths[index], "/");
		tmp_cmd = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(tmp_cmd, F_OK) == 0 && access(tmp_cmd, X_OK) == 0)
			return (tmp_cmd);
		free(tmp_cmd);
		index++;
	}
	return (NULL);
}

// void	mod_line(char *line, char *envp[])
// {
// 	t_data	data;

// 	data = parsing(line);
// 	data.path =	get_paths(envp);
// 	append_cmd(&data);
// 	execve(data.cmd[0].split[0], data.cmd[0].split, envp);
// }

void	interpret_line(char *line, char *envp[])
{
	// char *testargv[] = {"-e", "test.txt", NULL};
	char 		*cmd;
	t_tokens	*tokens;

	tokens = NULL;
	ft_printf("Received command: |%s|\n", line);
	if (!line)
		return ;
	cmd = get_cmd(get_paths(envp), line);
	if (!cmd)
		error_message("Failed to get command");
	else
		ft_printf("Got command: %s\n", cmd);
	parse(&tokens, line);
	ft_printf("Got tokens:\n");
	print_tokens(tokens);
	// data = parsing(line);
	// data.path =	get_paths(envp);
	// append_cmd(&data);
	// execve(data.cmd[0].split[0], data.cmd[0].split, envp);
}
