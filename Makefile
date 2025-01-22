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
SRC = $(shell find $(SRCDIR) -name '*.c')

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
