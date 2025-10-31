#pragma once

#include <iostream>
#include <vector>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class mv_CMD : public COMMAND
{
private:

    string source;
    string destination;

public:

    mv_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string keyword;
        ss >> keyword; // consume "mv"

        if (!(ss >> source))
            throw invalid_argument("mv: expected a file or directory name");

        if (regex_match(source, regex(path_file))) {
            if (!(ss >> destination))
                throw invalid_argument("mv: expected a destination");
            else if (!regex_match(destination, regex(path_file)) && !regex_match(destination, regex(path_dir)))
                throw invalid_argument("mv: '" + destination + "': invalid destination");
        }
        else if (regex_match(source, regex(path_dir))) {
            if (!(ss >> destination))
                throw invalid_argument("mv: expected a destination");
            else if (!regex_match(destination, regex(path_dir)))
                throw invalid_argument("mv: '" + destination + "': expected a directory");
        }
        else {
            if (source[0] == '-') throw invalid_argument("mv: no option supported");
            else throw invalid_argument("mv: '" + source + "': invalid source");
        }


        if (!ss.eof()) throw invalid_argument("mv: too many arguments");

        return true;
    }

    void execute() override {
        // pass
    }
};