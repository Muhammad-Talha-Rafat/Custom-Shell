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


vector<string> split(const string& cmd, const string& logic_op) {
    vector<string> result;
    size_t start = 0, end = 0;

    while ((end = cmd.find(logic_op, start)) != string::npos) {
        string token = cmd.substr(start, end - start);
        if (!token.empty())
            result.push_back(token);
        start = end + logic_op.length();
    }

    string last = cmd.substr(start);
    if (!last.empty())
        result.push_back(last);

    return result;
}


void trim(string& cmd) {
    int start = 0;
    int end = cmd.size() - 1;

    // Move from start and forward until first non-space
    while (start <= end && std::isspace(static_cast<unsigned char>(cmd[start]))) {
        ++start;
    }

    // Move from end and backward until last non-space
    while (end >= start && std::isspace(static_cast<unsigned char>(cmd[end]))) {
        --end;
    }

    cmd = cmd.substr(start, end - start + 1);
}

bool execute(const string& cmd, fs::path shell_location, tm* local) {

    if (cmd == "exit") exit(0);
    else if (cmd == "clear") system("clear");
    else if (cmd == "pwd")  cout << "\033[2;32m" << shell_location << "\033[0m"  << endl;
    else if (cmd == "time") cout << "\033[2;32m" << put_time(local, "%H:%M:%S") << "\033[0m" << endl;
    else if (cmd == "date") cout << "\033[2;32m" << put_time(local, "%Y-%m-%d") << "\033[0m" << endl;
    else if (cmd == "reset") reset();
    else try {
        auto command = COMMAND::dispatch(cmd);
        command->validate(cmd);
        command->execute();
    }
    catch (const exception& e) {
        cerr << "\033[0;31m" << e.what() << "\033[0m" << endl;
        return false;
    }
    return true;
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

    while (true) {
        ofstream out("history.log", ios::app);

        string cmd;
        string shell_location = noob.current_directory.string().substr(31);
        cout << "\033[0;32m" << shell_location << " $ " << "\033[0m";
        getline(cin, cmd);

        time_t now = time(nullptr);
        tm* local = localtime(&now);
        out << put_time(local, "%Y-%m-%d %H:%M:%S") << '\t' << cmd << '\n';

        vector<string> or_cmds = split(cmd, "||");
        bool or_success = false;

        for (auto& or_cmd : or_cmds) {

            vector<string> and_cmds = split(or_cmd, "&&");
            bool and_success = true;
            
            for (auto& and_cmd : and_cmds) {
                trim(and_cmd);
                bool success = execute(and_cmd, shell_location, local);
                if (!success) {
                    and_success = false;
                    break; // end if one AND group fails, go to next
                }
            }
            if (and_success) {
                or_success = true;
                break; // end if one OR group succeeds, return
            }
        }
    }
    return 0;
}
