NAME	= miniRT
CC		= gcc
# CFLAGS	= -Werror -Wall -Wextra $(INC) -g -fsanitize=thread
#CFLAGS	= -Werror -Wall -Wextra $(INC) -g -fsanitize=address
CFLAGS	= $(INC) -g -fsanitize=address

SRC_PATH = src
UTILS_PATH = utils
WRAPPER_PATH = wrapper
INCLUDE_PATH = include

SRCS	= 	src/ambient.c \
			src/bumpmap.c \
			src/color.c \
			src/color_utils.c \
			src/cone.c \
			src/cone_method.c \
			src/create_image.c \
			src/cylinder.c \
			src/cylinder_method.c \
			src/cylinder_method_helper.c \
			src/debug.c \
			src/free_utils.c \
			src/image.c \
			src/light.c \
			src/main.c \
			src/math.c \
			src/mlx_hooks.c \
			src/obj_info.c \
			src/object.c \
			src/object_method.c \
			src/object_radiance.c \
			src/plane.c \
			src/plane_method.c \
			src/read_rt_file.c \
			src/rt_params.c \
			src/rt_params_obj.c \
			src/rt_params_obj_info.c \
			src/scene.c \
			src/slice.c \
			src/slice_x.c \
			src/sphere.c \
			src/sphere_method.c \
			src/vector.c \
			src/vector_adv.c \
			src/vector_utils.c \
			utils/atoi_strict.c\
			utils/count_2d_array.c\
			utils/error.c\
			utils/free_2d_array.c\
			utils/ft_strtod.c\
			utils/get_next_line.c\
			utils/strappend.c \
			wrapper/x_close.c \
			wrapper/x_get_next_line.c \
			wrapper/x_malloc.c \
			wrapper/x_open.c \
			wrapper/x_split.c

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

all: $(NAME)

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

bonus: $(NAME)

norm:
	norminette $(SRCS) $(HEADERS)

norm-easy:
	norminette $(SRCS) $(HEADERS) | grep -v WRONG_SCOPE_COMMENT | grep -v LINE_TOO_LONG | grep -v "Missing or invalid header"

RT=proj2-4
run:
	./$(NAME) scenes/$(RT).rt

.PHONY: all bonus clean fclean re bonus
