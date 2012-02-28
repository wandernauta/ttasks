# This makefiles builds t, a no-nonsense no-nothing todo list.
# Check out the README file for more information.

SHELL = /bin/sh
CXXFLAGS = -g -ansi -O3 -Wall -Werror -Wextra -Winit-self -Wshadow -Wconversion -pedantic

all: t.cpp TodoList.hpp TodoList.cpp
	touch ~/todo.txt
	$(CXX) -o t $(CXXFLAGS) t.cpp TodoList.cpp

clean:
	rm t
	rm tags

tags:
	ctags *
