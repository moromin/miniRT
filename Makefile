NAME	= miniRT
CC		= gcc
CFLAGS	= -Werror -Wall -Wextra $(INC) -g -fsanitize=thread

SRC_PATH = src
UTILS_PATH = utils
WRAPPER_PATH = wrapper
INCLUDE_PATH = include

# TODO: write all out before submitting
SRC_PATHS	= $(SRC_PATH) $(UTILS_PATH) $(WRAPPER_PATH)
SRCS	= $(foreach path, $(SRC_PATHS), $(wildcard $(path)/*.c))

OBJDIR	= ./obj
OBJS    = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:%.c=%.o)))

VPATH = $(SRC_PATH):$(INCLUDE_PATH):$(UTILS_PATH):$(WRAPPER_PATH)

HEADERS = $(wildcard $(INCLUDE_PATH)/*.h)

X11		= /usr/X11/include
INC		= -I$(X11) -I$(MLX)
INCLIB	= $(X11)/../lib

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
	@make clean -C $(LIBFT)
	@make clean -C $(MLX)
	@rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME) $(CHECKER)

re: fclean all

norm:
	norminette $(SRCS) $(HEADERS) | grep -E '^(Error|Warning)'

norm-easy:
	norminette $(SRCS) $(HEADERS) | grep -v WRONG_SCOPE_COMMENT | grep -v LINE_TOO_LONG | grep -v "Missing or invalid header"

run:
	./$(NAME) scenes/proj2-4.rt

.PHONY: all bonus clean fclean re
