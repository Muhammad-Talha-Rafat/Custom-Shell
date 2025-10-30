#include "command.h"

#include "ls_CMD.h"
#include "cd_CMD.h"

unique_ptr<COMMAND> COMMAND::dispatch(const string& cmd) {
    stringstream ss(cmd);
    string token;
    ss >> token;

    if      (token == "ls") return make_unique<ls_CMD>(token);
    else if (token == "cd") return make_unique<cd_CMD>(token);
    else    throw invalid_argument(token + ": invalid command");
}
