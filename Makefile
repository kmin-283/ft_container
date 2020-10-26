# NAME = container

CC = clang++
CFLAGS = -std=c++98 -g3 -fsanitize=address
INCS =	Node/Node.hpp Iterator/Iterator.hpp List/List.hpp
SRCS = main_list.cpp main_vector.cpp

OBJS = $(SRCS:%.cpp=%.o)

# $(NAME):	$(OBJS)
# 			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o : %.cpp
			$(CC) $(CFLAGS) -o $@ -c $<

# all:		$(NAME)

list: $(OBJS)
			$(CC) $(CFLAGS) -o list_container main_list.cpp

vector: $(OBJS)
			$(CC) $(CFLAGS) -o vector_container main_vector.cpp			

clean:
			rm -rf $(OBJS)

fclean:
			rm -rf $(OBJS)
			rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re