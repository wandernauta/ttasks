#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <map>

typedef std::map<int, std::string> tmap;

class TodoList {
  public:
    TodoList();

    void add(std::string task);
    void erase(int num);
    std::string get(int num);
    void dump();
    int count();

    void parse();
    void edit();
    void write();
  private:
    tmap tasks;
    std::string path;
    int first_unset();
};

