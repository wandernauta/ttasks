#include "TodoList.hpp"

TodoList::TodoList() {
  path = std::string(getenv("HOME")) + "/todo.txt";
  parse();
}

void TodoList::add(std::string task) {
  unsigned int taskdesc = task.find_first_not_of("1234567890. ");
  if (taskdesc == std::string::npos) return;

  std::cout << "Added #" << first_unset() << ": " << task << std::endl;
  tasks[first_unset()] = task;
  write();
}

void TodoList::erase(int num) {
  std::cout << "Erased #" << num << ": " << tasks[num] << std::endl;
  tasks.erase(num);
  write();
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

int TodoList::count() {
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
      int taskno = atol(line.c_str());
      unsigned int taskdesc = line.find_first_not_of("1234567890. ");
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
  for (int i = 1; i < tasks.rbegin()->first; i++) {
    if (!tasks.count(i)) return i;
  }
  return tasks.rbegin()->first + 1;
}
