# NAME = container

CC = clang++
CFLAGS = -std=c++98 -fsanitize=address
INCS =	Node/Node.hpp Iterator/Iterator.hpp List/List.hpp

SRCS = $(addprefix ./tests/, main_list.cpp main_vector.cpp)

OBJS = $(SRCS:%.cpp=%.o)

LIST = $(addprefix ./tests/, main_list.cpp)
VECTOR = $(addprefix ./tests/, main_vector.cpp)


# $(NAME):	$(OBJS)
# 			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o : %.cpp
			$(CC) $(CFLAGS) -o $@ -c $<

# all:		$(NAME)

list: $(OBJS)
			$(CC) $(CFLAGS) -o list_container $(LIST)
			./list_container
			
vector: $(OBJS)
			$(CC) $(CFLAGS) -o vector_container $(VECTOR)
			./vector_container			

clean:
			rm -rf $(OBJS)
			rm -f list_container
			rm -f vector_container

fclean:
			rm -rf $(OBJS)
			rm -rf $(NAME)
			rm -f list_container
			rm -f vector_container

re: fclean all

relist : fclean list

revector : fclean vector

.PHONY: all clean fclean re