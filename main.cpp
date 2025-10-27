#include <iostream>
#include <set>
using namespace std;

set<string> CommandList = {
    "ls", "pwd", "cd", "mkdir", "rmdir", "rm",
    "cp", "mv",
    "cat", "head", "tail",
    "touch", "echo",
    "date", "time", "clear", "history", "exit", "help",
    "grep", "find"
};

int main() {
    for (const auto& command : CommandList) {
        cout << command << endl;
    }
}