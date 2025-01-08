# Nome do executável
NAME = Cub3d

# Diretórios
SRCDIR = Srcs
OBJDIR = Objs

# Compilador e flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Obtém todos os arquivos .c no diretório Srcs
SRC = $(shell find $(SRCDIR) -name '*.c')

# Substitui os sufixos dos arquivos .c por .o no diretório Objs
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

# Regra principal
all: $(NAME)

# Criação do executável
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Regra para compilar os objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

test:
	@./Tests/Map\ validation.sh

# Limpeza dos arquivos gerados
clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Ignora arquivos de regras automáticas
.PHONY: all clean fclean re
