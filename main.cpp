#include <iostream>
#include "resources/shell.h"
#include "resources/command.h"

using namespace std;
using namespace SHELL;

int main() {

    while (1) {
        string cmd;
        cout << "Playground $ ";
        getline(cin, cmd);
        try {
            auto command = COMMAND::dispatch(cmd);
            command->validate(cmd);
            command->execute();
        }
        catch (const exception& e) {
            cerr << "\033[1;31m" << e.what() << "\033[0m" << endl;
        }
    }
    
    return 0;
}

