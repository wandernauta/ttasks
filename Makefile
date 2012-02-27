t: t.cpp TodoList.hpp TodoList.cpp
	touch ~/todo.txt
	$(CXX) -o t -ansi -O3 -Wall -Werror -Wextra -Winit-self -Wshadow -Wconversion -pedantic t.cpp TodoList.cpp
