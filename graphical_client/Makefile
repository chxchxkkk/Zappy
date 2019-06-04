SRC =   $(wildcard src/*.cpp)

OBJ =   $(SRC:.cpp=.o)

NAME    =   graphical_client

CXX  =   g++

CXXFLAGS    =   -Wall -Wextra

LDFLAGS =   -lsfml-graphics -lsfml-system -lsfml-window

all:    $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(LDFLAGS) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all