# Variables
NAME = ext
CC = cc
FLAGS = -Wall -Werror -Wextra
SRCS = 	src/simul_ext_esqueleto.c	\
		src/print_bytemaps.c		\
		src/comprobar_comando.c		\
		src/lee_superbloque.c		\
		src/busca_fichero.c			\
		src/directorio.c			\
		src/renombrar.c				\
		src/imprimir.c				\
		src/borrar.c				\
		src/copiar.c				\
		src/grabar.c				\

# Rules
.PHONY: all flags clean fclean re

# Compiles project
all: $(NAME)

# Compiles ext from src files
$(NAME): $(SRCS)
	$(CC) $(SRCS) -o $(NAME)

# Compiles with -W flags
flags:
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

# Cleans temporary files but not the executable
clean:
	rm -f *.o

# Cleans the same as clean + the executable (full clean)
fclean: clean
	rm -f $(NAME)

# Cleans and recompiles ext
re: fclean all
