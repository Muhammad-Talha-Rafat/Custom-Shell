#pragma once

#include <iostream>
#include <vector>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class rm_CMD : public COMMAND
{
private:

    vector<string> filename;
    vector<string> directory;
    bool recursive = false;

public:
    rm_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "rm"

        if (!(ss >> token)) // only "rm"
            throw invalid_argument("rm: expected a filename or directory");

        if (token == "-r") {
            recursive = true;
            if (!(ss >> token)) // only "rm -r"
                throw invalid_argument("rm: expected a directory");
        }
        else if (token[0] == '-')
            throw invalid_argument("rm: invalid option '" + token + "'");

        if (recursive) do {
            if (regex_match(token, regex(path_dir)))
                directory.push_back(token);
            else throw invalid_argument("rm: '" + token + "': invalid directory");
        } while (ss >> token);
        else do {
            if (regex_match(token, regex(path_file)))
                filename.push_back(token);
            else throw invalid_argument("rm: '" + token + "': invalid filename");
        } while (ss >> token);

        return true;
    }

    void execute() override {
        // pass
    }
};