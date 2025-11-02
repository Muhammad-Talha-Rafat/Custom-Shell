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
    char option;
    size_t size;
    string redirection;
    string rdrfile;

public:

    tail_CMD(const string& token) {
        keyword = token;
        filename = "";
        option = '\0';
        size = 0;
        redirection = "";
        rdrfile = "";
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "tail"

        if (!(ss >> token))
            throw invalid_argument(keyword + ": expected a filename");

        if (token == "-n" || token == "-c") {
            option = token[1];
            ss >> token;
            if (regex_match(token, regex("[0-9]*")))
                size = stoi(token);
            else throw invalid_argument(keyword + ": '" + token + "': expected an integer");
            ss >> token;
        }
        else if (token[0] == '-')
            throw invalid_argument(keyword + ": '" + token + "': option not supported");

        if (token == "<")
            ss >> token; // ignore "<"

        if (regex_match(token, regex(path_file))) {
            if (!(ss >> token)) return true;
            if (token != ">" && token != ">>")
                throw invalid_argument(keyword + ": '" + token + "': expected a forward redirection");
            redirection = token;
            if(!(ss >> token))
                throw invalid_argument(keyword + ": expected a filename");
            else if (regex_match(token, regex(path_file)))
                rdrfile = token;
            else throw invalid_argument(keyword + ": '" + token + "': expected a filename");
        }
        else throw invalid_argument(keyword + ": '" + token + "': expected a filename");

        return true;
    }

    void execute() override {
        // pass
    }
};