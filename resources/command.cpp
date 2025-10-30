#include "command.h"

#include "ls_CMD.h"
#include "cd_CMD.h"
#include "mkdir_CMD.h"
#include "rmdir_CMD.h"
#include "rm_CMD.h"
#include "touch_CMD.h"

unique_ptr<COMMAND> COMMAND::dispatch(const string& cmd) {
    stringstream ss(cmd);
    string token;
    ss >> token;

    if      (token == "ls") return make_unique<ls_CMD>(token);
    else if (token == "cd") return make_unique<cd_CMD>(token);
    else if (token == "mkdir") return make_unique<mkdir_CMD>(token);
    else if (token == "rmdir") return make_unique<rmdir_CMD>(token);
    else if (token == "rm") return make_unique<rm_CMD>(token);
    else if (token == "touch") return make_unique<touch_CMD>(token);
    else    throw invalid_argument(token + ": invalid command");
}
