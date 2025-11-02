#ifndef USER_H
#define USER_H

#include <filesystem>
using namespace std;

struct USER {
    const filesystem::path home_directory = "E:/Kachra/OS Labs/Custom-Shell/Playground";
    filesystem::path current_directory;
    USER() : current_directory(home_directory) {}
};

extern USER noob;

#endif
