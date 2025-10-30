#include "command.h"
#include "ls_CMD.h"

unique_ptr<COMMAND> COMMAND::dispatch(const string& cmd) {
    stringstream ss(cmd);
    string keyword;
    ss >> keyword;

    if (keyword == "ls") return make_unique<ls_CMD>(cmd);
    else throw invalid_argument(keyword + ": invalid command");
}
