MAKEFLAGS += --silent

NAME = Cub3d

# Diretórios
SRCDIR = srcs
OBJDIR = Objs

# Diretório da biblioteca
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a
MINILIBX = libmlx.a
MINILIBXDIR = ./minilibx-linux
LDFLAGS = -L/usr/lib/x86_64-linux-gnu

# Compilador e flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFTDIR) -I$(SRCDIR) -g

SANFLAGS = -Wall -Wextra -Werror -I$(LIBFTDIR) -I$(SRCDIR) -g -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer

# Obtém todos os arquivos .c no diretório Srcs
SRC = $(shell find $(SRCDIR) -name '*.c')

# Substitui os sufixos dos arquivos .c por .o no diretório Objs
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

# Regra principal
all: $(NAME)

# Criação do executável
$(NAME): $(OBJ) $(LIBFT) $(MINILIBXDIR)/$(MINILIBX)
	@echo "Building!"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS) -L$(MINILIBXDIR) -lmlx -lm -lX11 -lXext $(MINILIBXDIR)/$(MINILIBX) && echo "Build completed!"

# Regra para compilar os objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar a biblioteca
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) && echo "Libft builded!"

# Minilibx
$(MINILIBXDIR)/$(MINILIBX):
	@make -C $(MINILIBXDIR) && echo MINILIBX Compilada

# San compilation
san: CFLAGS=$(SANFLAGS)
san: fclean $(OBJ) $(LIBFT) $(MINILIBXDIR)/$(MINILIBX)
	@echo "Building with sanitizers!"
	$(CC) $(SANFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS) -L$(MINILIBXDIR) -lmlx -lm -lX11 -lXext $(MINILIBXDIR)/$(MINILIBX)
	@echo "Sanitizer build completed!"
	@./Tests/Sanitize.sh
	make fclean

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
