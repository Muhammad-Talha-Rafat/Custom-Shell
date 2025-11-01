#ifdef _WIN32
#include <windows.h>
#endif

#include "resources/shell.h"
#include "resources/command.h"

using namespace std;
using namespace SHELL;

#include <iostream>
#include <iomanip>
#include <fstream>

int main() {

    // apply ANSI escape codes for colored output on cmd
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    #endif

    ofstream clear("history.log", ios::trunc);

    while (1) {
        ofstream out("history.log", ios::app);

        string cmd;
        cout << "Playground $ ";
        getline(cin, cmd);

        time_t now = time(nullptr);
        tm* local = localtime(&now);
        out << put_time(local, "%Y-%m-%d %H:%M:%S") << '\t' << cmd << '\n';

        if (cmd == "exit") break;
        else if (cmd == "clear") system("clear");
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
