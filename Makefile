NAME		:= minishell
READ_DIR	:= read
OBJS_DIR	:= objs
CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
RLFLAGS		:= -lreadline
RM		:= rm -rf
READ_SRCS	:= read/data_handler.c read/environment.c read/token_handler.c read/getters.c read/getters_utils.c read/expansion_utils.c read/help_expand.c
PARSE_SRCS	:= parse/parse.c parse/parse_utils.c
EXECUTE_SRCS	:= execute/exec_helpers.c execute/bi_exec.c execute/bi_cmds.c execute/bi_cmds_two.c execute/cmd_parsing.c execute/cmd_parsing_two.c execute/handle_args.c execute/handle_exec.c execute/handle_redirections.c execute/redir_processing.c execute/bi_utils.c execute/bi_utils_two.c execute/pipe_redir_handlers.c execute/exec_utils.c execute/exec_utils_two.c execute/exec_utils_three.c execute/manage_vars.c execute/manage_vars_utils.c execute/exec_core.c execute/exec_pipes.c execute/strtok.c execute/count_tks_until.c execute/create_file_tk.c
LIBFT_SRCS	:= libft/ft_utils.c libft/ft_utils_two.c libft/ft_utils_three.c libft/ft_utils_four.c libft/ft_utils_five.c
ROOT_SRCS	:= main.c free.c signal.c
SRCS		:= $(ROOT_SRCS) $(LIBFT_SRCS) $(READ_SRCS) $(PARSE_SRCS) $(EXECUTE_SRCS) 
OBJS        := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(RLFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: %.c | prepare_dir
	$(CC) $(CFLAGS) -c $< -o $@

prepare_dir:
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/libft $(OBJS_DIR)/read $(OBJS_DIR)/parse $(OBJS_DIR)/execute

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

