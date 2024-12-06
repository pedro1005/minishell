#include "../ms.h"

static void	update_cap(t_dyn_arr *data)
{
	void	*new_buf;

	data->arr_cap *= 2;
	new_buf = malloc(sizeof(void *) * data->arr_cap);
	memset(new_buf, 0, sizeof(void *) * data->arr_cap);
	ft_memcpy(new_buf, data->buf, data->len * sizeof(void *));
	free(data->buf);
	data->buf = NULL;
	data->buf = new_buf;
}

void	dyn_arr_push(t_dyn_arr *data, void *el)
{
	if (data->len >= data->arr_cap)
		update_cap(data);
	data->buf[data->len] = el;
	data->len++;
}

t_dyn_arr	dyn_arr_new(void)
{
	t_dyn_arr	arr;

	arr.len = 0;
	arr.arr_cap = INIT_CAP;
	arr.buf = (void **)malloc(sizeof(void *) * INIT_CAP);
	if (arr.buf)
		memset(arr.buf, 0, sizeof(void *) * INIT_CAP);
	return (arr);
}
