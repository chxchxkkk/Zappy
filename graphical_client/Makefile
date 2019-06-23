SRC =   $(wildcard src/*.cpp)

OBJ =   $(SRC:.cpp=.o)

NAME    =   zappy_graphic

CXX  =   g++

CXXFLAGS    =   -Wall -Wextra --std=c++14

LDFLAGS =   -lsfml-graphics -lsfml-system -lsfml-window -lpthread

all:    $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(LDFLAGS) $(OBJ)
	cp $(NAME) ..

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
