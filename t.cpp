#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cstring>

#include "TodoList.hpp"

int main(int argc, char* argv[]) {
  TodoList tl;
  std::vector<std::string> args(argv, argv+argc);

  if (argc == 1) {
    // Called as 't'. Dump the todo list.
    tl.dump();
  } else {
    if (args[1] == "-h") {
      // Called as 't -h': Dump some help info.
      std::cout << "usage: t               # Dump all items." << std::endl;
      std::cout << "       t 3             # Erase the third item." << std::endl;
      std::cout << "       t Walk the dog  # Add an item." << std::endl;
      std::cout << "       t -e            # Open todo.txt in $EDITOR." << std::endl;
      std::cout << "       t -h            # Show this help text." << std::endl;
      std::cout << "       t -c            # Count the amount of items." << std::endl;
      std::cout << std::endl;
      exit(0);
    } else if (args[1] == "-e") {
      // Called as 't -e'. Open todo.txt in $EDITOR.
      tl.edit();
    } else if (args[1] == "-c") {
      // Called as 't -c'. Count the amount of items in the list.
      std::cout << tl.count() << std::endl;
    } else if (args[1] == "0") {
      std::cout << "Say what?" << std::endl;
    } else if (atoi(argv[1]) != 0) {
      // Called as 't 3' or similar. Erase the task.
      tl.erase(atoi(argv[1]));
    } else {
      // Called as 't Walk the dog' or similar.
      // Collect the argument:

      std::ostringstream oss;
      std::copy(args.begin() + 1, args.end()-1, std::ostream_iterator<std::string>(oss, " "));
      oss << args.back();
      tl.add(oss.str());
    }
  }
}
