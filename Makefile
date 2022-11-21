# Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
NAME = ft_containers

CXX = clang++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g -Wno-long-long -pedantic-errors

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

HEADER_FILE = algorithm.hpp

HEADER = $(addprefix $(INCLUDES_PATH)/,$(HEADER_FILE))

SOURCE_FILES =	$(shell ls ./sources | grep .cpp$)

SOURCES = $(addprefix $(SOURCES_PATH)/,$(SOURCE_FILES))

OBJECTS = $(addprefix $(OBJECTS_PATH)/,$(subst .cpp,.o,$(SOURCE_FILES)))

# **************************************************************************** #

ifeq (test,$(firstword $(MAKECMDGOALS)))
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

test:
	@mkdir -p bin
	@$(CXX) -g -lrt -lm -Wall -Wextra -I $(INCLUDES_PATH) tests/$(RUN_ARGS).cpp -o bin/$(RUN_ARGS)
	@./bin/$(RUN_ARGS)

test_all:
	@mkdir -p bin
	@$(CXX) -lrt -lm -Wall -Wextra -I $(INCLUDES_PATH) tests/main.cpp -o bin/ft_containers
	@./bin/ft_containers
	@rm ./bin/ft_containers

clean:
	@$(REMOVE) $(OBJECTS_PATH)

fclean: clean
	@$(REMOVE) $(NAME)
	@rm -r bin

