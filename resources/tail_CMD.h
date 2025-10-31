#pragma once

#include <iostream>
#include <vector>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class tail_CMD : public COMMAND
{
private:

    string filename;
    string option;
    size_t size;
    string rdrfile;
    string redirection;

public:

    tail_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "tail"

        if (!(ss >> token))
            throw invalid_argument("tail: expected a filename");

        if (token == "-n" || token == "-c") {
            option = token;
            ss >> token;
            if (regex_match(token, regex("[0-9]*")))
                size = stoi(token);
            else throw invalid_argument("tail: '" + token + "': expected an integer");
            ss >> token;
        }
        else if (token[0] == '-')
            throw invalid_argument("tail: '" + token + "': option not supported");

        if (token == "<")
            ss >> token; // ignore "<"

        if (regex_match(token, regex(path_file))) {
            if (!(ss >> token)) return true;
            if (token != ">" && token != ">>")
                throw invalid_argument("tail: '" + token + "': expected a forward redirection");
            redirection = token;
            if(!(ss >> token))
                throw invalid_argument("tail: expected a filename");
            else if (regex_match(token, regex(path_file)))
                rdrfile = token;
            else throw invalid_argument("tail: '" + token + "': expected a filename 1");
        }
        else throw invalid_argument("tail: '" + token + "': expected a filename 2");

        return true;
    }

    void execute() override {
        // pass
    }
};