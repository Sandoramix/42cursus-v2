NAME=so_long

ROOTDIR=./src

LIBFTX_DIR=$(ROOTDIR)/libftx
MLX_DIR=$(ROOTDIR)/minilibx

# --------------
SRC = ./main.c \
	./src/enemies.c \
	./src/messages.c \
	./src/mlx_custom_draw.c \
	./src/mlx_events.c \
	./src/mlx_render.c \
	./src/parsing/check_path.c \
	./src/parsing/parsing.c \
	./src/textures.c \
	./src/utils.c


# ----RULES-----

CC=cc

INCLUDES=-I/usr/include/X11 -I$(ROOTDIR)/includes -I$(LIBFTX_DIR)/includes -I$(MLX_DIR)
CFLAGS=-Wall -Wextra -Werror $(INCLUDES) -g

RM=rm -rf



all: $(NAME)

$(NAME): $(SRC)
	@[ -d $(MLX_DIR) ] || $(MAKE) download-mlx
	$(MAKE) -C $(LIBFTX_DIR)
	$(MAKE) -sC $(MLX_DIR) && echo "$(GREEN)[MLX]:\t\tLIBRARY CREATED"
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -L$(LIBFTX_DIR) -lft -L$(MLX_DIR) -lmlx_$(shell uname) -lXext -lX11 -o $@
	@echo "$(GREEN)[SO_LONG]:\tPROGRAM CREATED$(R)"

clean:
	@$(MAKE) -iC $(MLX_DIR) clean || echo -n ""
	@$(MAKE) -C $(LIBFTX_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFTX_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(BLUE)[SO_LONG]:\tPROGRAM DELETED$(R)"

# --------------

re: fclean all

# ----UTILS-----
VALGRIND=@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes
valgrind: all
	@$(VALGRIND) ./$(NAME) $(mapfile)
valgrindre: re valgrind

MLX_LINK=https://github.com/42Paris/minilibx-linux/archive/refs/heads/master.zip
download-mlx:
	echo "$(BLUE) Downloading MLX...$(R)";
	wget $(MLX_LINK) -O minilibx-linux.zip || (echo "$(RED)SOMETHING WENT WRONG WITH MLX LINK. PLEASE UPDATE IT$(R)"; exit 1)
	unzip minilibx-linux.zip
	mv minilibx-linux-master $(ROOTDIR)/minilibx
	$(RM) minilibx-linux.zip*


remove-mlx:
	@$(RM) $(MLX_DIR) && echo "$(GREEN)[MLX]:\t\tDELETED MINILIBX FOLDER!"


# ----OTHER-----
.PHONY: all clean fclean re valgrind
.SILENT:

# ----COLORS----
GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
R=\033[0m
# --------------
