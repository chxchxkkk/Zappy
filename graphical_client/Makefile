SRC =   $(wildcard src/*.cpp)

OBJ =   $(SRC:.cpp=.o)

NAME    =   graphical_client

CXX  =   g++

CXXFLAGS    =   -Wall -Wextra --std=c++14 -g

LDFLAGS =   -lsfml-graphics -lsfml-system -lsfml-window -lpthread

all:    $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(LDFLAGS) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
