#pragma once

#include <iostream>
#include <vector>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class mkdir_CMD : public COMMAND
{
private:

    vector<string> directory;

public:
    mkdir_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "mkdir"

        if (ss.eof())
            throw invalid_argument(keyword + ": expected a directory"); // only "mkdir"

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