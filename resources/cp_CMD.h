#pragma once

#include <iostream>
#include <vector>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class cp_CMD : public COMMAND
{
private:

    string source;
    string destination;
    bool recursive = false;

public:

    cp_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "cp"

        if (!(ss >> token))
            throw invalid_argument("cp: expected a file or directory name");

        if (regex_match(token, regex(path_file))) {
            source = token;
            if (!(ss >> destination))
                throw invalid_argument("cp: expected a destination");
            else if (!regex_match(destination, regex(path_file)) && !regex_match(destination, regex(path_dir)))
                throw invalid_argument("cp: '" + destination + "': invalid destination");
        }
        else if (regex_match(token, regex(path_dir)))
            throw invalid_argument("cp: missing '-r' option");
        else if (token == "-r") {
            recursive = true;
            if (!(ss >> source))
                throw invalid_argument("cp: expected a source directory");
            else if (!regex_match(source, regex(path_dir)))
                throw invalid_argument("cp: '" + source + "': invalid source");
            if (!(ss >> destination))
                throw invalid_argument("cp: expected a destination");
            else if (!regex_match(destination, regex(path_dir)))
                throw invalid_argument("cp: '" + destination + "': invalid destination");
        }
        else if (token[0] == '-')
            throw invalid_argument("cp: invalid option '" + token + "'");
        else throw invalid_argument("cp: invalid format");

        if (!ss.eof()) throw invalid_argument("cp: too many arguments");

        return true;
    }

    void execute() override {
        // pass
    }
};