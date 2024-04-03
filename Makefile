NAME = miniRT

LIBMLX = ./MLX42

# MLX = $(LIBMLX)/build/libmlx42.a -Iinclude -lglfw -L/opt/homebrew/Cellar/glfw/3.4/lib/
MLX = $(LIBMLX)/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -L/opt/homebrew/Cellar/glfw/3.4/lib/
#-L/usr/loca/Cellar/glfw/lib/

LIBS = $(MLX)

INCLUDES = -I ./inc/ -I $(LIBMLX)/include/MLX42

SRCS = $(addprefix srcs/, \
	hit.c \
	interval.c \
	main.c \
	material.c \
	utilities.c \
	ray.c \
	sphere_diffuse.c \
	vec3a.c \
	vec3b.c \
	vec3c.c \
	vector_array.c \
	)

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -Wpedantic -Wtype-limits -o3 $(INCLUDES)

all: libmlx $(NAME)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJS): $(SRCS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
