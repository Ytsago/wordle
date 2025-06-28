NAME = backend.a

SRCDIR = src
OBJDIR = obj
INCDIR = include
LIBFTDIR = libft
LIBFTINC = $(LIBFTDIR)/include

SRCS = $(addprefix $(SRCDIR)/, \
		parse_file.c \
		get_random_word.c \
		run_wordle.c \
		is_in_word_list.c \
		get_feedback.c \
		free_dic.c)
		#main.c)

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

LIBFT = $(LIBFTDIR)/libft.a

AR = ar
ARFLAGS = -rcs
CFLAGS = -Wall -Wextra -Werror -g3 -I $(INCDIR) -I $(LIBFTINC)
DEBUGFLAGS = -pg
DEPFLAGS = -MMD -MP
MAKEFLAGS = --no-print-directory

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(AR) -x libft/libft.a
	$(AR) $(ARFLAGS) -o $@ *.o $^ $(LDFLAGS)
	rm *.o

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

debug: $(OBJS) $(LIBFT)
	$(CC) $(DEBUGFLAGS) -o $@ $^

-include $(DEPS)

.PHONY: all clean fclean re bonus FORCE
