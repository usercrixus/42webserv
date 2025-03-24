NAME = webserv

SRC_FILES = src/main \
		src/Socket/WebservSocket \
		src/Socket/Socket \
		src/Socket/WebServSocketRunner \
		src/Request/Request \
		src/Response/Response \
		src/Response/mimes \
		src/Method/MethodPost \
		src/Method/MethodGet \
		src/Method/MethodDelete \
		src/Method/IMethod \
		src/Config/Parsing/parsing \
		src/Config/Parsing/Limit \
		src/Config/Data/Data \
		src/Config/Data/File \
		src/Config/Data/Route \
		src/Config/Data/Methods \
		src/Config/Data/Server \
		src/Config/Data/Http \
		src/CGI/Cgi \

INC_FILES = src/Socket/WebservSocket \
		src/Socket/Socket \
		src/Socket/WebServSocketRunner \
		src/Request/Request \
		src/Response/Response \
		src/Method/MethodPost \
		src/Method/MethodGet \
		src/Method/MethodDelete \
		src/Method/IMethod \
		src/Config/Parsing/parsing \
		src/Config/Parsing/Limit \
		src/Config/Data/Data \
		src/Config/Data/File \
		src/Config/Data/Route \
		src/Config/Data/Methods \
		src/Config/Data/Server \
		src/Config/Data/Http \
		src/CGI/Cgi \

INC	= $(addsuffix .hpp, $(INC_FILES))
SRC	= $(addsuffix .cpp, $(SRC_FILES))
OBJ	= $(addsuffix .o, $(SRC_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	c++ $^ -o $@

%.o: %.cpp $(INC)
	c++ -std=c++98 -g3 -Wall -Werror -Wextra -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
