MAKEFLAGS += --silent

NAME = Cub3d

# Diretórios
SRCDIR = Srcs
OBJDIR = Objs

# Diretório da biblioteca
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

# Compilador e flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFTDIR)

# Obtém todos os arquivos .c no diretório Srcs
SRC = $(shell find $(SRCDIR) -name '*.c')

# Substitui os sufixos dos arquivos .c por .o no diretório Objs
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

# Regra principal
all: $(NAME)

# Criação do executável
$(NAME): $(OBJ) $(LIBFT)
	@echo "Building!"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) && echo "Build completed!"

# Regra para compilar os objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar a biblioteca
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) && echo "Libft builded!"

test:
	@./Tests/Map\ validation.sh

# Limpeza dos arquivos gerados
clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

# Ignora arquivos de regras automáticas
.PHONY: all clean fclean re
