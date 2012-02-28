#include "TodoList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

TodoList::TodoList() {
  path = std::string(getenv("HOME")) + "/todo.txt";
  parse();
}

void TodoList::add(std::string task) {
  if (task.find_first_not_of("1234567890. ") == std::string::npos) return;

  std::cout << "Added #" << first_unset() << ": " << task << std::endl;
  tasks.insert(std::make_pair(first_unset(), task));
  write();
}

void TodoList::erase(int num) {
  if (tasks.count(num)) {
    std::cout << "Erased #" << num << ": " << tasks[num] << std::endl;
    tasks.erase(num);
    write();
  } else {
    std::cerr << "There is no task #" << num << "." << std::endl;
  }
}

std::string TodoList::get(int num) {
  std::ostringstream oss;
  oss << num;
  oss << ". ";
  oss << tasks[num];
  return oss.str();
}

void TodoList::dump() {
  tmap::iterator it;

  for (it = tasks.begin(); it != tasks.end(); ++it) {
    std::cout << get(it->first) << std::endl;
  }
}

std::map<int, std::string>::size_type TodoList::count() {
  return tasks.size();
}

void TodoList::parse() {
  tasks.clear();

  std::ifstream ifs(path.c_str());

  if (!ifs.good()) {
    std::cerr << "Fatal: Can't open " << path.c_str() << "." << std::endl;
    exit(1);
  }

  while (ifs.good()) {
    std::string line = "";
    getline(ifs, line);

    if (line != "") {
      int taskno = atoi(line.c_str());
      std::string::size_type taskdesc = line.find_first_not_of("1234567890. ");
      if (taskdesc == std::string::npos) continue;
      tasks[taskno] = std::string(line, taskdesc); 
    }
  }
}

void TodoList::edit() {
  std::string cmd = "env $EDITOR " + path;
  system(cmd.c_str());
}

void TodoList::write() {
  std::ofstream ofs(path.c_str());

  tmap::iterator it;

  for (it = tasks.begin(); it != tasks.end(); ++it) {
    ofs << get(it->first) << std::endl;
  }

  ofs.close();
}

int TodoList::first_unset() {
  if (tasks.size()) {
    for (int i = 1; i < tasks.rbegin()->first; i++) {
      if (!tasks.count(i)) return i;
    }
    return tasks.rbegin()->first + 1;
  } else {
    return 1;
  }
}
