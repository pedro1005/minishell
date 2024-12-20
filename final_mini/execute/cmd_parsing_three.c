/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:23:13 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/17 15:23:38 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

int	count_args(t_token **tokens, int index, int *i)
{
	int	count;

	count = 0;
	*i = index + 1;
	while (tokens[*i] && tokens[*i]->type.sub_tk == TK_ARG)
	{
		count++;
		(*i)++;
	}
	return (count);
}

char	**ft_get_args(t_token **tokens, int index)
{
	int		n;
	int		i;
	int		j;
	char	**args;

	i = index + 1;
	j = 0;
	n = count_args(tokens, index, &i);
	if (n == 0)
		return (NULL);
	i = i - n - 1;
	n++;
	args = (char **)malloc(sizeof(char *) * (n + 2));
	if (!args)
		return (NULL);
	while (n > 0)
	{
		args[j++] = ft_strdup(tokens[i]->s);
		i++;
		n--;
	}
	args[j] = NULL;
	return (args);
}

//get_redir() helper

void	check_errno(char *args)
{
	write(2, args, ft_strlen(args));
	write(2, ": ", 2);
	if (errno == ENOENT)
	{
		write(2, "file not found\n", 15);
		g_signals = 2;
	}
	else if (errno == EACCES)
	{
		write(2, "permission denied\n", 18);
		g_signals = 13;
	}
	else
	{
		write(2, "error: ", 7);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		g_signals = 1;
	}
}

int	ft_check_err_args(char **args)
{
	struct stat	file_stat;
	int			i;

	i = 0;
	while (args && args[i])
	{
		if (stat(args[i], &file_stat) == 0)
			i++;
		else
		{
			check_errno(args[i]);
			return (1);
		}
	}
	return (0);
}
