#pragma once

#include <iostream>
#include <vector>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class echo_CMD : public COMMAND
{
private:

    vector<string> text;
    string filename;
    bool recursive = false;
    string redirect_out;

public:

    echo_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "echo"

        if (token == "<")
            ss >> token; // ignore input redirection

        if (ss.eof())
            throw invalid_argument("echo: some text was expected"); // only "echo" or "echo <"
        
        while (ss >> token && token != ">" && token != ">>") {
            if (regex_match(token, regex("\"[^\"]*\"")))
                text.push_back(token);
            else throw invalid_argument("echo : '" + token + "': expected some text");
        }

        if (ss >> token) { // redirection
            if (token == ">" || token == ">>") {
                redirect_out = token;
                ss >> token;
                if (!regex_match(token, regex(path_file)))
                    throw invalid_argument("echo: invalid filename after '" + redirect_out + "'");
                else filename = token;
            }
            else throw invalid_argument("echo: '" + token + "': unexpected argument");
        }

        return true;
    }

    void execute() override {
        // pass
    }
};