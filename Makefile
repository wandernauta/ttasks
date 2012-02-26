t: t.cpp TodoList.hpp TodoList.cpp
	$(CXX) -o t -ansi -O3 -Wall -Werror -Wextra -Winit-self -Wshadow -Wconversion -Wunreachable-code -pedantic t.cpp TodoList.cpp
