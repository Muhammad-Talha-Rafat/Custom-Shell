#pragma once

#include <memory>

using namespace std;

class ls_CMD;
class cd_CMD;

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
