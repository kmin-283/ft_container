NAME = container

CC = clang++
CFLAGS = -std=c++98 -Wall -Werror -Wextra

INCS =	Node/Node.hpp Iterator/Iterator.hpp List/List.hpp\
		Vector/vector.hpp

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