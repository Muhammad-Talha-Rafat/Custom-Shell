#pragma once

#include <iostream>
#include <vector>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class cat_CMD : public COMMAND
{
private:

    string filename;
    string redirection;
    string rdrfile;

public:

    cat_CMD(const string& token) {
        keyword = token;
        filename = "";
        redirection = "";
        rdrfile = "";
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "cat"

        if (ss.eof()) throw invalid_argument(keyword + ": expected a filename");

        if (ss >> token) {
            if (token == "<") ss >> token; // ignore "<" 
            if (token[0] == '-') throw invalid_argument(keyword + ": '" + token + "': no options supported");
            else if (regex_match(token, regex(path_file)))
                filename = token;
            else throw invalid_argument(keyword + ": '" + token + "': expected a filename");
        }

        if (ss >> token) {
            if (token == ">" || token == ">>")
                redirection = token;
            else throw invalid_argument(keyword + ": '" + token + "': expected a forward redirection");

            if (!(ss >> token))
                throw invalid_argument(keyword + ": '" + token + "': expected a filename");
            else if (regex_match(token, regex(path_file)))
                rdrfile = token;
            else throw invalid_argument(keyword + ": '" + token + "': invalid filename");
        }

        if (!ss.eof()) throw invalid_argument(keyword + ": too many arguments");

        return true;
    }

    void execute() override {
        // pass
    }
};