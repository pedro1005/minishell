/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:08:16 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:08:19 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	g_signals;

t_dyn_arr	*ft_init_tokens(void)
{
	t_dyn_arr	*tokens;

	tokens = (t_dyn_arr *)malloc(sizeof(t_dyn_arr));
	if (!tokens)
		return (NULL);
	ft_memset(tokens, 0, sizeof(t_dyn_arr));
	*tokens = dyn_arr_new();
	return (tokens);
}

t_dyn_arr	*tokenize(t_dyn_arr *env, const char *in)
{
	t_dyn_arr	*tokens;
	t_lexer		lexer;
	t_token		*token;

	tokens = ft_init_tokens();
	token = NULL;
	lexer = (t_lexer){.input = in, .is_heredoc = false};
	while (true)
	{
		token = get_token(env, &lexer);
		if (token && (ft_strcmp(token->s, (const char *)"") == 0))
		{
			free (token->s);
			free(token);
			continue ;
		}
		else if (token)
			dyn_arr_push(tokens, token);
		else
			break ;
	}
	dyn_arr_push(tokens, NULL);
	return (tokens);
}

int	ft_check_quote_error(char *in)
{
	int		get_error;
	int		i;
	char	quote;

	i = 0;
	get_error = 0;
	while (in && in[i])
	{
		if (in[i] == '\'' || in[i] == '"')
		{
			quote = in[i++];
			get_error = 1;
			while (in[i] && in[i] != quote)
				i++;
			if (in[i] == quote)
			{
				get_error = 0;
				i++;
			}
		}
		else
			i++;
	}
	return (get_error);
}

static size_t	mechanism(t_terminal *terminal, const char *in)
{
	t_dyn_arr	*tokens;

	if (ft_check_quote_error((char *)in))
	{
		write(2, "unended quote.\n", 15);
		g_signals = 1;
		return (1);
	}
	tokens = tokenize(&terminal->envt, in);
	if (parse(tokens, terminal))
		return (1);
	g_signals = 0;
	execute(terminal);
	ft_free_cmds(terminal);
	return (0);
}

void	rpel(t_terminal *terminal)
{
	char	*in;

	while (true)
	{
		set_signal();
		in = readline("Minishell>> ");
		if (!in)
		{
			printf("exit\n");
			free(in);
			break ;
		}
		else if (ft_is_all_whitespace(in))
		{
			free(in);
			continue ;
		}
		add_history(in);
		if (mechanism(terminal, in))
		{
			free(in);
			continue ;
		}
		free(in);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_terminal		terminal;

	(void)argc;
	(void)argv;
	g_signals = 0;
	ft_memset(&terminal, 0, sizeof(t_terminal));
	terminal.envp = env_init(envp);
	terminal.envt = env_init(envp);
	rpel(&terminal);
	ft_free_args((char **)terminal.envp.buf);
	ft_free_args((char **)terminal.envt.buf);
	rl_clear_history();
	return (0);
}
