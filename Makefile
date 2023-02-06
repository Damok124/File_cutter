NAME = libfile_cutter.a

BINARY = file_cutter

LIBFT = libft/libft.a

LIBFT_PRINTF = ft_printf/libft_printf.a

SRCSDIR = ./srcs/

SRCS = \
${SRCSDIR}ft_full_file_cutter.c

HEADERDIR = includes/

HEADER = file_cutter.h

OBJ = $(SRCS:.c=.o)

CC = clang

FLAGS = -Wall -Wextra -Werror -g3

IFLAG = -I$(HEADERDIR) -Ift_printf/includes/ -Ilibft/includes/

all : $(BINARY)

$(BINARY) : $(NAME) $(LIBFT_PRINTF) $(LIBFT)
	@$(CC) $(FLAGS) main.c $(IFLAG) -L. -lfile_cutter -L./libft -lft \
	-L./ft_printf -lft_printf -o $(BINARY)

%.o : %.c
	@$(CC) $(FLAGS) $(IFLAG) -o $@ -c $^

$(NAME) : $(OBJ) $(HEADERDIR)$(HEADER)
	@ar -rcs $(NAME) $^

$(LIBFT_PRINTF) :
	@${MAKE} -sC ft_printf/

$(LIBFT) :
	@${MAKE} -sC libft/

clean :
	@rm -f $(OBJ)
	@${MAKE} clean -sC ft_printf/
	@${MAKE} clean -sC libft/

fclean : clean
	@rm -f $(NAME)
	@rm -f $(BINARY)
	@${MAKE} fclean -sC ft_printf/
	@${MAKE} fclean -sC libft/

re : fclean all

dev :
	@rm -f $(BINARY)
	@${MAKE} -sC ./

.PHONY : all clean fclean re dev
