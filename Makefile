NAME	= miniRT
CC		= gcc
CFLAGS	= -Werror -Wall -Wextra $(INC) -g -fsanitize=thread

SRCDIR	= ./src
SRCS	= $(wildcard $(SRCDIR)/*.c) # TODO: write all out before submitting
OBJDIR	= ./obj
OBJS    = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

X11		= /usr/X11/include
INC		= -I$(X11) -I$(MLX) -Iinclude
INCLIB	= $(X11)/../lib
INCLUDE	= include/miniRT.h
VPATH	= src

MLX		= minilibx-linux
LIBFT	= libft

LFLAGS	= -L$(MLX) -lmlx -L$(LIBFT) -lft -L$(INCLIB) -lXext -lX11 -lm

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	LFLAGS += -lbsd
endif

all: $(NAME) run

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@make -C $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LFLAGS)

$(OBJDIR)/%.o: %.c
	@if [ ! -d $(dir $@) ];then mkdir $(dir $@); fi
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make clean -C $(MLX)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME) $(CHECKER)

re: fclean all

norm:
	norminette $(SRCS) $(HEADERS) | grep -E '^(Error|Warning)'

run:
	./$(NAME)

.PHONY: all bonus clean fclean re
