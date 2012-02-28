# This makefiles builds t, a no-nonsense no-nothing todo list.
# Check out the README file for more information.

SHELL ?= /bin/sh
CXXFLAGS ?= -g -ansi -O3 -Wall -Werror -Wextra -Winit-self -Wshadow -Wconversion -pedantic
INSTALL_PATH ?= /usr/local

all: t.cpp TodoList.hpp TodoList.cpp
	touch ~/todo.txt
	$(CXX) -o t $(CXXFLAGS) t.cpp TodoList.cpp

clean:
	rm -f t
	rm -f tags

tags:
	ctags *

install:
	install ./t $(INSTALL_PATH)/bin

uninstall:
	rm -i $(INSTALL_PATH)/bin/t
