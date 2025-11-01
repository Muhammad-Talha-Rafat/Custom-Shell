#pragma once

#include <memory>
#include <string>

using namespace std;

class ls_CMD;
class cd_CMD;
class mkdir_CMD;
class rmdir_CMD;
class rm_CMD;
class touch_CMD;
class echo_CMD;
class cp_CMD;
class mv_CMD;
class cat_CMD;
class head_CMD;
class tail_CMD;
class grep_CMD;
class find_CMD;
class pwd_MISC;
class date_MISC;
class time_MISC;
class help_MISC;
class history_MISC;

class COMMAND
{
protected:

    string keyword;

public:

    COMMAND() = default;

    virtual bool validate(const string& cmd) = 0;
    virtual void execute() = 0;

    static unique_ptr<COMMAND> dispatch(const string& cmd);

    virtual ~COMMAND() = default;
};