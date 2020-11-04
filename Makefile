# NAME = container

CC = clang++
CFLAGS = -std=c++98
INCS =	Node/Node.hpp Iterator/Iterator.hpp List/List.hpp

SRCS = $(addprefix ./tests/, main_list.cpp main_vector.cpp)

OBJS = $(SRCS:%.cpp=%.o)

LIST = $(addprefix ./tests/, main_list.cpp)
VECTOR = $(addprefix ./tests/, main_vector.cpp)
MAP = $(addprefix ./tests/, main_map.cpp)

# $(NAME):	$(OBJS)
# 			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o : %.cpp
			$(CC) $(CFLAGS) -o $@ -c $<

# all:		$(NAME)

list: $(OBJS)
			$(CC) $(CFLAGS) -o list_container $(LIST) -I ./List
			./list_container
			
vector: $(OBJS)
			$(CC) $(CFLAGS) -o vector_container $(VECTOR) -I ./Vector
			./vector_container

map: $(OBJS)
			$(CC) $(CFLAGS) -o map_container $(MAP) -I ./Map
			./map_container

clean:
			rm -rf $(OBJS)
			
fclean: clean
			rm -rf $(NAME)
			rm -f list_container
			rm -f vector_container
			rm -f map_container

re: fclean all

relist : fclean list

revector : fclean vector

remap : fclean map

.PHONY: all clean fclean re