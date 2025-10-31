#pragma once

#include <iostream>
#include <vector>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class head_CMD : public COMMAND
{
private:

    vector<string> filename;
    bool recursive = false;

public:

    head_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "touch"

        if (!(ss >> token))
            throw invalid_argument("touch: missing file name");

        do {
            if (regex_match(token, regex(path_file)))
                filename.push_back(token);
            else throw invalid_argument("touch: '" + token + "': expected a file name");
        } while (ss >> token);

        return true;
    }

    void execute() override {
        // pass
    }
};