NAME = container

CC = clang++
CFLAGS = -Wall -Werror -Wextra

INCS =	Node/Node.hpp Iterator/Iterator.hpp ConstIterator/ConstIterator.hpp\
		List/List.hpp
SRCS = main.cpp

OBJS = $(SRCS:%.cpp=%.o)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o : %.cpp
			$(CC) $(CFLAGS) -o $@ -c $<

all:		$(NAME)

clean:
			rm -rf $(OBJS)

fclean:
			rm -rf $(OBJS)
			rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re