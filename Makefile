MAKEFLAGS += --silent

NAME = Cub3d

# Diretórios
INCDIR = code/inc
SRCDIR = code/srcs
OBJDIR = code/objs
LIBDIR = code/lib

# Diretório da biblioteca
LIBFTDIR = $(LIBDIR)/libft
MINILIBXDIR = $(LIBDIR)/minilibx-linux
LIBFT = $(LIBFTDIR)/libft.a
MINILIBX = libmlx.a

# Compilador e flags
CC = cc
IFLAGS = -I$(INCDIR) -I$(LIBFTDIR) -I$(MINILIBXDIR) 
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -L$(LIBFTDIR) -L$(MINILIBXDIR) -lft -lmlx -lm -lX11 -lXext

SANFLAGS = -Wall -Wextra -Werror $(IFLAGS) -g -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer

# Obtém todos os arquivos .c no diretório Srcs
#SRC = $(shell find $(SRCDIR) -name '*.c')
SRC = code/srcs/draw_tools/draw_line.c code/srcs/draw_tools/put_pixel_img.c code/srcs/keys/player_movement.c \
	code/srcs/keys/player_rotation.c code/srcs/keys/read_keys.c code/srcs/map/file_init.c code/srcs/map/map_allocation.c \
	code/srcs/map/map_allocation_2.c code/srcs/map/map_aux.c code/srcs/map/map_aux_2.c code/srcs/map/map_validation.c \
	code/srcs/map/map_validation_2.c code/srcs/map/map_verification.c code/srcs/map/map_verification2.c code/srcs/renderer/pixel_line_builder.c \
	code/srcs/renderer/ray_caster.c code/srcs/update_loop/update.c code/srcs/time_utils/delta_time.c code/srcs/frees/freeEverything.c code/srcs/main.c
# Substitui os sufixos dos arquivos .c por .o no diretório Objs
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

# Regra principal
all: $(NAME)

# Criação do executável
$(NAME): $(OBJ) $(LIBFT) $(MINILIBXDIR)/$(MINILIBX)
	@echo "Building!"
	$(CC) $(IFLAGS) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME) && echo "Build completed!"

# Regra para compilar os objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

# Regra para compilar a biblioteca
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) && echo "Libft builded!"
	@$(MAKE) clean -C $(LIBFTDIR)

# Minilibx
$(MINILIBXDIR)/$(MINILIBX):
	@make -C $(MINILIBXDIR) && echo MINILIBX Compilada

# San compilation
san: CFLAGS=$(SANFLAGS)
san: fclean $(OBJ) $(LIBFT) $(MINILIBXDIR)/$(MINILIBX)
	@echo "Building with sanitizers!"
	$(CC) $(IFLAGS) $(CFLAGS) $(OBJ) $(LFLAGS) $(SANFLAGS) -o $(NAME) && echo "Sanitizer build completed!"
	@./Tests/Sanitize.sh

test: $(NAME)
	@./Tests/Map\ validation.sh

allowed_fun:
	@./Tests/AllowedFunctions.sh ./Cub3d

val: all
	@./Tests/Valgrind.sh	

san: $(SAN)

# Limpeza dos arquivos gerados
clean:
	@echo "Clean"
	rm -rf $(OBJDIR)
	@cd $(MINILIBXDIR) && make clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean
	@echo "Binarios apagados!"

re: fclean all

# Ignora arquivos de regras automáticas
.PHONY: all clean fclean re
