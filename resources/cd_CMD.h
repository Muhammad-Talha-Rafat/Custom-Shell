#pragma once

#include <iostream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class cd_CMD : public COMMAND
{
private:

    string directory = "";

public:
    cd_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "cd"

        if (ss >> token) {
            if (regex_match(token, regex(path_dir)) || token == "~")
                directory = token;
            else throw invalid_argument(keyword + ": expected a directory");
            if (ss >> token)
                throw invalid_argument(keyword + ": too many arguments");
        }
        return true; // only "cd"
    }

    void execute() override {
        // pass
    }
};