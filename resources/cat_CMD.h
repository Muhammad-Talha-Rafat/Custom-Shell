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

    vector<string> filename;
    string redirect_out;
    bool recursive = false;

public:

    cat_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "cat"

        if (ss.eof()) throw invalid_argument("cat: expected a file name");

        if (ss >> token) {
            if (token == "<") ss >> token; // ignore "<" 
            if (token[0] == '-') throw invalid_argument("cat: '" + token + "': no options supported");
            else if (regex_match(token, regex(path_file)))
                filename.push_back(token);
            else throw invalid_argument("cat: '" + token + "': expected a file name");
        }

        if (ss >> token) {
            if (token == ">" || token == ">>")
                redirect_out = token;
            else throw invalid_argument("cat: '" + token + "': expected a forward redirection");

            if (!(ss >> token))
                throw invalid_argument("cat: '" + token + "': expected a file name");
            else if (regex_match(token, regex(path_file)))
                filename.push_back(token);
            else throw invalid_argument("cat: '" + token + "': invalid file name");
        }

        if (!ss.eof()) throw invalid_argument("cat: too many arguments");

        return true;
    }

    void execute() override {
        // pass
    }
};