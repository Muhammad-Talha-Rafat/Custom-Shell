#pragma once

#include <iostream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class ls_CMD : public COMMAND
{
private:

    bool long_format = false;
    string directory = "";
    string filename = "";
    string output_redirection;

public:
    ls_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "ls"
        
        if (ss >> token) {
            if (token == "-l") {
                long_format = true;
                if (!(ss >> token))
                    return true; // only "ls -l"
            }
            else if (token[0] == '-')
                throw invalid_argument(keyword + ": invalid option '" + token + "'");
        }
        else return true; // only "ls"
        
        if (token == "<") {
            if (!(ss >> token)) // ignore "<"
                throw invalid_argument(keyword + ": expected a directory after '<'");
            if (!regex_match(token, regex(path_dir)))
                throw invalid_argument(keyword + ": invalid directory '" + token + "'");
            directory = token;
            if (!(ss >> token)) 
                return true; // command ended after "< folder"
        }
        
        if (directory.empty() && regex_match(token, regex(path_dir))) {
            directory = token;
            if (!(ss >> token))
                return true; // command ended after "folder"
        }
        
        if (token == ">" || token == ">>") {
            output_redirection = token;
            if (!(ss >> filename))
                throw invalid_argument(keyword + ": expected a filename after '" + output_redirection + "'");
            if (!regex_match(filename, regex(path_file)))
                throw invalid_argument(keyword + ": invalid filename '" + filename + "'");
            if (ss >> token)
                throw invalid_argument(keyword + ": too many arguments");
            return true; // command ended after ">/>> filename"
        }

        throw invalid_argument(keyword + ": unexpected token '" + token + "'");
    }

    void execute() override {
        // pass
    }
};