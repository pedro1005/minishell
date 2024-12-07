#include "../ms.h"

static bool	is_last_status(char *arg)
{
	while (arg && *arg != '$')
		arg++;
	return (ft_strncmp("$?", arg, 2) == 0);
}

char	*help_expand(char *buf, t_dyn_arr *env, char *var)
{
	char	*l_status;
	char	*var_value;

	if (is_last_status(buf))
	{
		l_status = ft_itoa(g_signals);
		buf = replace_var(buf, var, l_status);
		free(l_status);
	}
	else if (pos_env_var(env, var + 1) != -1)
	{
		var_value = get_var_value(env->buf[pos_env_var(env, var + 1)]);
		buf = replace_var(buf, var, var_value);
	}
	else
		buf = replace_var(buf, var, "");
	return (buf);
}
