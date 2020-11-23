# NAME = container

CC = clang++
CFLAGS = -std=c++98 -fsanitize=address
INCS =	Node/Node.hpp Iterator/Iterator.hpp List/List.hpp

SRCS = $(addprefix ./tests/, main_list.cpp main_vector.cpp main_map.cpp main_stack.cpp main_queue.cpp \
								main_set.cpp)

OBJS = $(SRCS:%.cpp=%.o)

LIST = $(addprefix ./tests/, main_list.cpp)
VECTOR = $(addprefix ./tests/, main_vector.cpp)
MAP = $(addprefix ./tests/, main_map.cpp)
STACK = $(addprefix ./tests/, main_stack.cpp)
QUEUE = $(addprefix ./tests/, main_queue.cpp)
SET = $(addprefix ./tests/, main_set.cpp)


TEST_RESULT = $(addprefix ./result/, my stl)

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
			diff $(TEST_RESULT) > ./result/result || exit 0

stack: $(OBJS)
			$(CC) $(CFLAGS) -o stack_container $(STACK) -I ./Stack
			./stack_container
			diff $(TEST_RESULT) > ./result/result || exit 0

queue: $(OBJS)
			$(CC) $(CFLAGS) -o queue_container $(QUEUE) -I ./Queue
			./queue_container
			diff $(TEST_RESULT) > ./result/result || exit 0

set: $(OBJS)
			$(CC) $(CFLAGS) -o set_container $(SET) -I ./Set
			./set_container
			diff $(TEST_RESULT) > ./result/result || exit 0

clean:
			rm -rf $(OBJS)
			
fclean: clean
			rm -rf $(NAME)
			rm -f list_container
			rm -f vector_container
			rm -f map_container
			rm -f stack_container
			rm -f queue_container
			rm -f set_container
			rm -f $(TEST_RESULT)

re: fclean all

relist : fclean list

revector : fclean vector

remap : fclean map

restack : fclean stack

requeue : fclean queue

reset : fclean set

.PHONY: all clean fclean re