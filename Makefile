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
		src/Config/Parsing/parsing.o \
		src/Config/Parsing/Limit.o \
		src/Config/Data/Data.o \
		src/Config/Data/File.o \
		src/Config/Data/Route.o \
		src/Config/Data/Methods.o \
		src/Config/Data/Server.o \
		src/Config/Data/Http.o \
		src/Config/Data/Events.o \
		src/CGI/Cgi.o \

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
