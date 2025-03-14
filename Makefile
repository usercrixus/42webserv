NAME = webserv

OBJ = \
		src/main.o \
		src/Socket/WebservSocket.o \
		src/Socket/Socket.o \
		src/Request/Request.o \
		src/Response/Response.o \
		src/Method/MethodPost.o \
		src/Method/MethodGet.o \
		src/Method/MethodDelete.o \
		src/Method/IMethod.o \

all: $(NAME)

$(NAME): $(OBJ)
	c++ $^ -o $@

%.o: %.cpp
	c++ -std=c++98 -Wall -Werror -Wextra -c $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
