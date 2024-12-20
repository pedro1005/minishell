/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte & gamado-x <marvin@42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:06:37 by pedmonte          #+#    #+#             */
/*   Updated: 2024/12/11 19:06:41 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# define INIT_CAP 4

# define LIT_REDIR_OUT ">"
# define LIT_REDIR_IN "<"
# define LIT_REDIR_APPEND ">>"
# define LIT_REDIR_DEL "<<"
# define LIT_PIPE "|"
# define LIT_QUOTE '\''
# define LIT_DOUBLE_QUOTE '"'

extern int	g_signals;

typedef enum e_bi
{
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT,
}	t_bi;

typedef enum e_tk_maintype
{
	TK_UNKNOWN,
	TK_WORD,
	TK_OPERATOR,
	TK_COMMAND,
}	t_tk_maintype;

typedef enum e_tk_subtype
{
	TK_NONE,
	TK_BUILT_IN,
	TK_EXEC,
	TK_ARG,
	TK_FILENAME,
	TK_PATH,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_REDIR_APP,
	TK_REDIR_HERE,
	TK_EQL,
	TK_EOF,
}	t_tk_subtype;

typedef struct s_type
{
	t_tk_maintype	main_tk;
	t_tk_subtype	sub_tk;
}	t_type;

typedef struct s_op_type
{
	t_tk_subtype	type;
	char			*symbol;
}	t_op_type;

typedef struct s_dyn_arr
{
	size_t	len;
	size_t	arr_cap;
	void	**buf;
}	t_dyn_arr;

typedef struct s_token
{
	bool	literal;
	char	*s;
	t_type	type;
}	t_token;

typedef struct s_exec
{
	char	*name;
	char	**args;
	t_type	type;
}	t_exec;

typedef struct s_redir
{
	t_type	type_in;
	t_type	type_out;
	char	**args_in;
	char	**delim;
	t_exec	*exec;
	int		err;
	t_token	**args_out;
}	t_redir;

typedef struct s_tree
{
	t_exec				*exec;
	t_redir				*redir;
	int					fd[2];
	pid_t				pid;
	int					status;
	struct s_tree		*right_tree;
	struct s_tree		*left_tree;

}	t_tree;

typedef struct s_terminal
{
	int			exit;
	int			fd_cp[2];
	int			is_fd0;
	t_dyn_arr	envp;
	t_dyn_arr	envt;
	t_tree		*commands;

}	t_terminal;

typedef struct s_lexeme
{
	size_t		i;
	const char	*input;
	bool		has_heredoc;
}	t_lexeme;

//libft
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_isspace(int c);
int					ft_is_all_whitespace(char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little, \
					size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_itoa(int n);
char				*ft_strjoin(char const *s1, char const *s2);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(char *str, const char *dest);
int					ft_atoi(const char *str);
int					ft_isnumber(char *str);

//frees
void				ft_free_exe(t_exec *exec);
void				ft_free_args(char **args);
void				ft_free_redir(t_tree *cmd);
void				ft_free_cmds(t_terminal *terminal);
void				ft_free_tokens(t_dyn_arr *tokens);
void				free_dyn_arr(t_dyn_arr dy_arr);

//signal handler
void				set_signal(void);
void				set_child_sig(void);
void				set_heredoc_sig(void);
t_terminal			*get_terminal(t_terminal *new);

//read
t_dyn_arr			dyn_arr_new(void);
void				dyn_arr_push(t_dyn_arr *data, void *el);
t_dyn_arr			env_init(char **envp);
int					pos_env_var(t_dyn_arr *env, char *find);
char				*get_var_value(char *var);

//parse
char				*replace_var(const char *s, const char *sub, \
					const char *with);
char				*help_expand(char *buf, t_dyn_arr *env, char *var);
char				*dollar_sign(const char *s);
char				*expand_token(const char *token, t_dyn_arr *env);
void				ft_set_subtype(t_token **tokens);
t_tk_subtype		ft_get_op_subtype(const char *input);
t_tk_subtype		ft_get_cmd_subtype(const char *input);
int					ft_check_quote_error(char *in);
int					parse(t_dyn_arr *tokens, t_terminal *terminal);
t_tk_subtype		ft_get_wrd_subtype(t_token **input, int i);
int					ft_is_operator(const char *str);
void				ft_set_tktype(t_token **tokens);
int					ft_is_builtin(char *s);
int					synt_err_msg(char *token);
int					ft_get_synt_err(t_token **tokens);
t_token				*get_token(t_dyn_arr *env, t_lexeme *lx);
char				*join_next(t_lexeme *lx, const char *token, \
					t_dyn_arr *env, bool is_quoted);
char				*get_normal(t_lexeme *lx, size_t i, t_dyn_arr *env);
char				*get_string(t_lexeme *lx, size_t i, t_dyn_arr *env);
char				*get_operator(t_lexeme *lx);

//execute
void				ft_export(t_terminal *terminal, char **args);
void				ft_pwd(void);
char				*ft_get_pwd(void);
char				*ft_getenv(char **env, char *str);
void				ft_exit(t_terminal *terminal, t_exec *bi);
void				ft_cd(char **path, t_terminal *terminal);
void				ft_echo(char **args);
void				ft_unset(t_terminal *terminal, char **token);
void				ft_print_export(char **envp);
void				ft_execbi(t_exec *bi, t_terminal *terminal);
void				ft_env(t_dyn_arr env);
void				echo_util(char **args, int *nflag, int *i);
void				export_utils(t_terminal *term, int *i, char **args);
void				unset_utils(char **envp, char **token, t_dyn_arr env, \
					int *i);
void				cd_utils(char *home, char *oldpwd, char *current_pwd, \
					t_terminal *term);
void				cd_utils_two(char *home, char *oldpwd, char *current_pwd, \
					t_terminal *term);
void				exec_bi_util(char *name, t_terminal *term, t_exec *bi);
char				**ft_get_args(t_token **tokens, int index);
int					ft_check_err_args(char **args);
t_tree				*ft_get_cmds(t_token **tokens);
t_tree				*ft_get_pipe(t_token **tokens, int *index);
char				**ft_get_delim(t_token **tokens, int index);
t_exec				*ft_get_exec_r(t_token **tokens, int index);
char				**ft_get_args_i(t_token **tokens, int index);
int					ft_count_tks_until_op(t_token **tokens, int *i);
t_token				*create_file_token(t_token *current, t_token *previous);
void				ft_execve(t_exec *exec, t_terminal *terminal);
void				ft_execnode(t_tree *node, t_terminal *terminal);
void				ft_exec_redir(t_redir *redir, t_terminal *terminal, \
					int hd_input_fd);
void				execute(t_terminal *terminal);
void				ft_wait_child(t_tree *root, t_terminal *terminal);
void				write_here_doc(int write_fd, char **delim, \
					t_terminal *terminal);
void				ft_abst(t_terminal *terminal);
void				abst_exec(t_tree *root, t_terminal *terminal, \
					int hd_input_fd);
int					fd_output(t_token **args);
void				init_loop_values(int *pipe, int *hd_in);
void				ft_close_fd(int fd[2]);
char				*ft_fullpath(char *path, const char *name);
void				set_fd(int fd[2], int num);
void				ft_exec_fd_child(t_exec *exec, int input_fd, \
					int output_fd, t_terminal *terminal);
int					fd_input(char **args);
int					ft_create_pipe(int fd[2], pid_t *pid);
void				execute_command(char *full_path, t_exec *exec, \
					t_terminal *term);
void				path_exec_cmds(char *full_path, char *name, \
					t_terminal *term, t_exec *exec);
void				create_pipe(t_tree *root, int *pipe_fd, int *pipecreated);
void				ft_fill_args_loop(char **args, t_token **tokens, \
					int *i, int *j);
char				**ft_get_rdrexargs(t_token **tokens, int index);
t_exec				*ft_get_redir_ex(t_token **tokens, int index);
void				ft_handle_redirections(char **args, t_token **tokens, \
					int *i, int *j);
t_token				**ft_get_args_o(t_token **tokens, int index);
void				ft_set_redir_type(t_redir *redir, t_token **tokens, \
					int index);
char				*get_var_name(char *var);
char				*ft_get_clean_var_name(char *var);
int					ft_var_exist(char **env, char *var);
void				ft_add_var(t_dyn_arr *envp, char *var);
char				*ft_vardup(char **env, char *var_name);
void				check_next_pipe(t_tree *root, int pipe_fd[2], \
					int *pipe_created);
int					check_heredoc(t_tree *root, int *hd_input_fd, \
					t_terminal *terminal);
int					handle_here_document(char **delim, t_terminal *terminal);
int					handle_input_redir(t_redir *redir, int *input_fd);
int					handle_output_redir(t_redir *redir, int *input_fd, \
					int *output_fd);
t_redir				*ft_get_redir(t_token **tokens, int index);
char				*ft_strtok(char *str, const char *delim);
void				export_utils(t_terminal *term, int *i, char **args);

static inline char	*get_char(const t_lexeme *lx, size_t i)
{
	return ((char *)lx->input + i);
}

#endif 
