NAME = ft_retro

SRC = *.cpp

all: $(NAME)

$(NAME):
	clang++ -Wall -Wextra -Werror -o $(NAME) $(SRC) -lncurses

clean:
	/bin/rm -rf *~ a.out \#*\# *.gch *.o

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all
