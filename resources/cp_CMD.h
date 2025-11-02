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
    bool _r;

public:

    cp_CMD(const string& token) {
        keyword = token;
        source = "";
        destination = "";
        _r = false;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "cp"

        if (!(ss >> token))
            throw invalid_argument(keyword + ": expected a file or directory");

        if (regex_match(token, regex(path_file))) {
            source = token;
            if (!(ss >> destination))
                throw invalid_argument(keyword + ": expected a destination");
            else if (!regex_match(destination, regex(path_file)) && !regex_match(destination, regex(path_dir)))
                throw invalid_argument(keyword + ": '" + destination + "': invalid destination");
        }
        else if (regex_match(token, regex(path_dir)))
            throw invalid_argument(keyword + ": missing '-r' option");
        else if (token == "-r") {
            _r = true;
            if (!(ss >> source))
                throw invalid_argument(keyword + ": expected a source directory");
            else if (!regex_match(source, regex(path_dir)))
                throw invalid_argument(keyword + ": '" + source + "': invalid source");
            if (!(ss >> destination))
                throw invalid_argument(keyword + ": expected a destination");
            else if (!regex_match(destination, regex(path_dir)))
                throw invalid_argument(keyword + ": '" + destination + "': invalid destination");
        }
        else if (token[0] == '-')
            throw invalid_argument(keyword + ": '" + token + "': invalid option");
        else throw invalid_argument(keyword + ": invalid format");

        if (!ss.eof()) throw invalid_argument(keyword + ": too many arguments");

        return true;
    }

    void execute() override {
        // pass
    }
};