FLAGS = -Wall -Wextra -Werror -g

NAME = philo

SRCS = philo.c \

OBJS = $(SRCS:.c=.o)

.c.o:
	@cc $(FLAGS) -c $(SRCS) -I .

all : $(NAME)

$(NAME): $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $(NAME)

clean: $(OBJS)
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	@make all

.PHONY: all clean fclean re