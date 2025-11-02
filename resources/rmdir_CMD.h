#pragma once

#include <iostream>
#include <vector>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class rmdir_CMD : public COMMAND
{
private:

    vector<string> directory;

public:
    rmdir_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "rmdir"

        if (ss.eof())
            throw invalid_argument(keyword + ": expected a directory"); // only "rmdir"

        while (ss >> token) {
            if (regex_match(token, regex(path_dir)))
                directory.push_back(token);
            else throw invalid_argument(keyword + ": '" + token + "': invalid directory");
        }

        return true;
    }

    void execute() override {
        // pass
    }
};