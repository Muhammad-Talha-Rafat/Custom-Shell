#ifdef _WIN32
#include <windows.h>
#endif

#include "resources/shell.h"
#include "resources/command.h"
#include "resources/user.h"

using namespace std;
using namespace SHELL;

#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>

USER noob;


void reset() {
    noob.current_directory = noob.home_directory;
    filesystem::path home_directory = noob.home_directory;

    if (filesystem::exists(home_directory))
        filesystem::remove_all(home_directory);

    filesystem::create_directories(home_directory);

    for (const auto& [key, path_str] : file_path) {
        filesystem::path file_path_obj(path_str);
        filesystem::create_directories(file_path_obj.parent_path());
        ofstream out(file_path_obj);
        out << file_content.at(key);
        out.close();
    }

    system("clear");
}


int main() {

    // apply ANSI escape codes for colored output on cmd
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    #endif

    reset();

    ofstream clear("history.log", ios::trunc);

    while (1) {
        ofstream out("history.log", ios::app);

        string cmd;
        string shell_location = noob.current_directory.string().substr(31);
        cout << shell_location << " $ ";
        getline(cin, cmd);

        time_t now = time(nullptr);
        tm* local = localtime(&now);
        out << put_time(local, "%Y-%m-%d %H:%M:%S") << '\t' << cmd << '\n';

        if (cmd == "exit") break;
        else if (cmd == "clear") system("clear");
        else if (cmd == "pwd")  cout << "\033[2;32m" << shell_location << "\033[0m"  << endl;
        else if (cmd == "time") cout << put_time(local, "%H:%M:%S") << endl;
        else if (cmd == "date") cout << put_time(local, "%Y-%m-%d") << endl;
        else if (cmd == "reset") reset();
        else try {
            auto command = COMMAND::dispatch(cmd);
            command->validate(cmd);
            command->execute();
        }
        catch (const exception& e) {
            cerr << "\033[0;31m" << e.what() << "\033[0m" << endl;
        }
    }
    
    return 0;
}

