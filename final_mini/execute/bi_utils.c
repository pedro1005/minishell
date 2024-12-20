/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:00:55 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:00:57 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

void	unset_utils(char **envp, char **token, t_dyn_arr env, int *i)
{
	char	*name;
	int		j;
	int		k;

	k = 1;
	name = get_var_name(envp[*i]);
	while (token[k])
	{
		if (ft_strcmp(token[k], name) == 0)
		{
			free(envp[*i]);
			j = *i;
			while (envp[j + 1])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			envp[j] = NULL;
			env.len--;
		}
		k++;
	}
	(*i)++;
	free(name);
}

void	cd_utils_two(char *home, char *oldpwd, char *current_pwd,
			t_terminal *term)
{
	char	*pwd;

	pwd = ft_get_pwd();
	oldpwd = ft_strjoin("OLDPWD=", current_pwd);
	if (ft_var_exist((char **)term->envp.buf, oldpwd))
		ft_add_var(&term->envp, oldpwd);
	ft_add_var(&term->envt, oldpwd);
	free(oldpwd);
	free(current_pwd);
	current_pwd = ft_strjoin("PWD=", pwd);
	if (ft_var_exist((char **)term->envp.buf, current_pwd))
		ft_add_var(&term->envp, current_pwd);
	ft_add_var(&term->envt, current_pwd);
	free(current_pwd);
	free(home);
	free(pwd);
}

void	cd_check_home(char *home)
{
	if (chdir(home) != 0)
	{
		write(2, "cd: ", 4);
		write(2, home, ft_strlen(home));
		write(2, ": No such file or directory\n", 28);
		g_signals = 1;
	}
}

void	cd_utils(char *home, char *oldpwd, char *current_pwd, t_terminal *term)
{
	if (!home)
	{
		write(2, "cd: HOME not set\n", 17);
		free(current_pwd);
	}
	else
	{
		cd_check_home(home);
		oldpwd = ft_strjoin("OLDPWD=", current_pwd);
		if (ft_var_exist((char **)term->envp.buf, oldpwd))
			ft_add_var(&term->envp, oldpwd);
		ft_add_var(&term->envt, oldpwd);
		free(oldpwd);
		free(current_pwd);
		current_pwd = ft_strjoin("PWD=", home);
		if (ft_var_exist((char **)term->envp.buf, current_pwd))
			ft_add_var(&term->envp, current_pwd);
		ft_add_var(&term->envt, current_pwd);
		free(current_pwd);
		current_pwd = NULL;
		free(home);
		home = NULL;
	}
	g_signals = 0;
	return ;
}

void	exec_bi_util(char *name, t_terminal *term, t_exec *bi)
{
	if (ft_strcmp((char *)name, "unset") == 0)
	{
		if (bi->args && bi->args[1])
			ft_unset(term, bi->args);
		else
		{
			g_signals = 0;
			return ;
		}
	}
	else if (ft_strcmp((char *)name, "env") == 0)
		ft_env(term->envp);
	else if (ft_strcmp((char *)name, "exit") == 0)
		ft_exit(term, bi);
	else if (bi->type.sub_tk == TK_EQL)
	{
		ft_add_var(&term->envt, bi->name);
		if (ft_var_exist((char **)term->envp.buf, bi->name))
			ft_add_var(&term->envp, bi->name);
	}
}
