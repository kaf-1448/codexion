CC = cc 
FALGS = -Wall -Wextra -Werror 
SRCS = src/main.c src/ft_parsing.c
OBJS = $(SRCS:.c=.o)
NAME = codexion

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(FALGS) $^ -o $@

%.o:%.c
	$(CC) $(FALGS) -c $< -o $@

clean: 
	rm -rf $(OBJS)

fclean:clean 
	rm -rf $(NAME)

re:fclean all

.PHONY: clean, re, all, fclean