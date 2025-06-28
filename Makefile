NAME = minishell

SRCDIR = src
OBJDIR = obj
INCDIR = include
LIBFTDIR = lib/libft
LIBFTINC = $(LIBFTDIR)/include

SRCS = $(addprefix $(SRCDIR)/, \
		init.c \
		terminate.c \
		get_paths.c \
		get_paths_copy.c \
		parsing/parser.c \
		parsing/tokenization/tokenize.c \
		parsing/tokenization/remove_quote.c \
		parsing/tokenization/remove_parentheses.c \
		parsing/tokenization/check_token_type/get_operator_type.c \
		parsing/tokenization/check_token_type/command/is_builtin.c \
		parsing/tokenization/get_next_token.c \
		parsing/tokenization/get_command_path.c \
		parsing/tokenization/check_token_type/get_token_type.c \
		parsing/tokenization/check_token_type/is_redir.c \
		parsing/tokenization/check_token/check_token.c \
		parsing/tokenization/check_token/pre_check.c \
		parsing/fill_ast.c \
		parsing/find_expand.c \
		parsing/expanding/expander.c \
		parsing/expanding/expand_var.c \
		parsing/expanding/fix_vector.c \
		parsing/expanding/get_next_expand.c \
		parsing/expanding/get_var_len.c \
		parsing/expanding/join_new.c \
		parsing/expanding/join_void.c \
		parsing/expanding/join_return.c \
		expand_variable.c \
		wildcard/expand_wildcard.c \
		remove_env_var.c \
		prompt.c \
		executable/output_utils.c\
		free_ast.c \
		free_env.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/exec_builtins.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/pwd.c \
		builtins/unset.c \
		builtins/export_utils.c \
		pipe/handle_child.c \
		pipe/pipe_parent.c \
		pipe/pipe.c \
		executable/and.c \
		executable/exec.c \
		executable/executable.c \
		executable/open_output_file.c \
		executable/redirect_stdout.c \
		executable/heredoc.c \
		executable/input.c \
		executable/fork.c \
		executable/is_builtins.c \
		executable/or.c \
		executable/heredoc_utils2.c \
		executable/output.c \
		executable/create_tab.c \
		executable/deep_tree.c \
		strtoll/strtoll1.c \
        strtoll/strtoll2.c \
        signal.c \
        is_num_valid.c \
		executable/print_ascii.c \
		executable/heredoc_utils.c \
		random/get_random_char.c \
		random/get_random_alphanum.c \
		random/get_random_tmp.c \
		get_address.c \
		main.c)

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

LIBFT = $(LIBFTDIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -g3 -I $(INCDIR) -I $(LIBFTINC)
DEBUGFLAGS = -pg
DEPFLAGS = -MMD -MP
LDFLAGS = -lreadline -lncurses
MAKEFLAGS = --no-print-directory

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFTDIR)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean
	make all

bonus: $(BONUS_NAME)

debug: $(OBJS) $(LIBFT)
	$(CC) $(DEBUGFLAGS) -o $@ $^

-include $(DEPS)
-include $(BONUS_DEPS)

.PHONY: all clean fclean re bonus FORCE