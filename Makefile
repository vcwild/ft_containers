# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 19:19:40 by vwildner          #+#    #+#              #
#    Updated: 2022/10/24 16:44:52 by vwildner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g -pedantic -Wshadow=local -fsanitize=address

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

# **************************************************************************** #

SAFE_MKDIR = mkdir -p

COPY = cp -p

REMOVE = rm -rf

OBJECTS_PATH = $(PWD)/objects
SOURCES_PATH = $(PWD)/sources
INCLUDES_PATH = $(PWD)/includes
LIBS_PATH = $(PWD)/libs
ARCHIVES_PATH = $(PWD)/archives

# **************************************************************************** #

HEADER_FILE = ft_containers.hpp

HEADER = $(addprefix $(INCLUDES_PATH)/,$(HEADER_FILE))

SOURCE_FILES =	$(shell ls ./sources | grep .cpp$)

SOURCES = $(addprefix $(SOURCES_PATH)/,$(SOURCE_FILES))

OBJECTS = $(addprefix $(OBJECTS_PATH)/,$(subst .cpp,.o,$(SOURCE_FILES)))

# **************************************************************************** #

ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

# **************************************************************************** #

.PHONY: all run valgrind re fclean clean test

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER) $(ALL_LIBS)
	@$(CXX) $(CXXFLAGS) \
	-w $(OBJECTS) \
	-o $(NAME) \
	-L $(ARCHIVES_PATH) \
	-I $(INCLUDES_PATH)

$(OBJECTS_PATH)/%.o: $(SOURCES_PATH)/%.cpp $(HEADER)
	@$(SAFE_MKDIR) $(OBJECTS_PATH)
	@$(CXX) $(CXXFLAGS) -I $(INCLUDES_PATH) -o $@ -c $<

test: $(NAME)
	@./$(NAME)

clean:
	@$(REMOVE) $(OBJECTS_PATH)

fclean: clean
	@$(REMOVE) $(NAME)
