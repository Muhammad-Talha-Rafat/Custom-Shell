#include "command.h"

#include "ls_CMD.h"
#include "cd_CMD.h"
#include "mkdir_CMD.h"
#include "rmdir_CMD.h"
#include "rm_CMD.h"
#include "touch_CMD.h"
#include "echo_CMD.h"
#include "cp_CMD.h"
#include "mv_CMD.h"
#include "cat_CMD.h"
#include "head_CMD.h"
#include "tail_CMD.h"
#include "grep_CMD.h"
#include "find_CMD.h"
#include "misc_CMD.h"


unique_ptr<COMMAND> COMMAND::dispatch(const string& cmd) {
    stringstream ss(cmd);
    string token;
    ss >> token;

    if      (token == "ls")      return make_unique<ls_CMD>(token);
    else if (token == "cd")      return make_unique<cd_CMD>(token);
    else if (token == "mkdir")   return make_unique<mkdir_CMD>(token);
    else if (token == "rmdir")   return make_unique<rmdir_CMD>(token);
    else if (token == "rm")      return make_unique<rm_CMD>(token);
    else if (token == "touch")   return make_unique<touch_CMD>(token);
    else if (token == "echo")    return make_unique<echo_CMD>(token);
    else if (token == "cp")      return make_unique<cp_CMD>(token);
    else if (token == "mv")      return make_unique<mv_CMD>(token);
    else if (token == "cat")     return make_unique<cat_CMD>(token);
    else if (token == "head")    return make_unique<head_CMD>(token);
    else if (token == "tail")    return make_unique<tail_CMD>(token);
    else if (token == "grep")    return make_unique<grep_CMD>(token);
    else if (token == "find")    return make_unique<find_CMD>(token);
    else if (token == "pwd")     return make_unique<pwd_MISC>();
    else if (token == "help")    return make_unique<help_MISC>();
    else if (token == "history") return make_unique<history_MISC>();
    else                         throw invalid_argument(token + ": invalid command");
}
