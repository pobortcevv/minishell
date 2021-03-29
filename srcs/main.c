/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 21:45:13 by sabra             #+#    #+#             */
/*   Updated: 2021/03/29 16:40:19 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

t_sh shell;

void		ft_test_pr(t_list *first)
{
	t_list	*t;
	t_cmd	*ex;
	int		i;

	t=first; while (t != NULL)
	{
		i = 0;
		printf("инструкция:\n");
		ex = (t_cmd *)(t->content);
		printf("id = %d\n", ex->id);
		while (ex->args[i] != NULL)
		{
			printf("%s\n", (char *)(ex->args[i]));
			i++;
		}
		t = t->next;
	}
	return ;
}

int			init_command(t_cmd *cmd, char **envp)
{
	char *path;
	char *filename;

	path = ft_var_find("PATH", envp);
	if ((ft_strcmp(cmd->args[0], "pwd")) == 0)
		return (ft_pwd(cmd->out));
	if ((ft_strcmp(cmd->args[0], "env")) == 0)
		return (ft_env(envp, cmd->out));
	if ((ft_strcmp(cmd->args[0], "echo")) == 0)
		return (ft_echo(cmd));
	if ((ft_strcmp(cmd->args[0], "exit")) == 0)
		return (ft_exit(cmd));
	else if ((filename = ft_find_bin(cmd->args[0], path)))
		return (ft_exec_bin(cmd, filename, envp));
	if (path)
		ft_free_line(&path);
	return (1);
}

char			**ft_exec_cmd(t_cmd *ar_cmd, char **env, int cmd_count)
{
	int i;

	i = 0;
	while (i < cmd_count)
	{
		if ((ft_strncmp(ar_cmd[i].args[0], "unset", ft_strlen(ar_cmd[i].args[0]))) == 0)
			env = ft_unset(&ar_cmd[i], env);
		else if ((ft_strncmp(ar_cmd[i].args[0], "export", ft_strlen(ar_cmd[i].args[0]))) == 0)
			env = ft_export(&ar_cmd[i], env);
		else if ((ft_strncmp(ar_cmd[i].args[0], "cd", ft_strlen(ar_cmd[i].args[0]))) == 0)
			env = ft_cd(&ar_cmd[i], env);
		else
			shell.status = init_command(&ar_cmd[i], env);
		if (shell.status == 1)
		{
			ft_putstr_fd("minishell: ", ar_cmd[i].out);
			ft_putstr_fd(ar_cmd[i].args[0], ar_cmd[i].out);
			ft_putendl_fd(": command not found", ar_cmd[i].out); 
		}
		i++;
	}
	return (env);
}

int			main(int argc, char **argv, char **envp)
{
	char		*str;
	char		**evc=NULL;
	int			gnl;
	int 		res;

	str = NULL;
	ft_bzero(&shell, sizeof(t_sh));
	evc = ft_copy_envp(envp);
	evc = ft_init_envp(evc);
	sig_init();
	while (1)
	{
		ft_printf("minishell> ");
		gnl = get_next_line(0, &str);
		if (gnl == 0 && *str == '\0')
			ft_exit(NULL);
		evc = ft_parser_shell(evc, str);
		if (!evc)
		{
			printf("Error with shell\n");
			break ;
		}
		if (str)
			free(str);
	}
	ft_free_mat(evc);
	if (str)
		free(str);
	if (argc && argv[0] && envp[0])
		;
	return (0);
}
