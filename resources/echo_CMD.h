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
    string redirection;
    string rdrfile;

public:

    echo_CMD(const string& token) {
        keyword = token;
        redirection = "";
        rdrfile = "";
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "echo"

        while (ss >> token) {
            if (token == "<")
                ss >> token; // ignore "<" 

            if (token == ">" || token == ">>") {
                if (text.empty()) throw invalid_argument(keyword + ": expected some text before '" + token + "'");
                else break;
            }

            if (token[0] == '"') { 
                string literal = token;
                while (token[token.length() - 1] != '"') {
                    if (ss.eof())                                                           //  ends without running if there's only one literal,
                        throw invalid_argument(keyword + ": unexpected end to the string"); //  otherwise keeps on consuming tokens until it either
                    ss >> token;                                                            //  finds a token ending with ", or the command ends.
                    literal += " " + token;                                                 //  literal can be "text", "more text" or "even more text"
                }
                text.push_back(literal);
            }
            else throw invalid_argument(keyword + ": '" + token + "': expected some text instead");
        }

        if (text.empty() && ss.eof())
            throw invalid_argument(keyword + ": expected some text after '" + token + "'");
        else if (ss.eof())
            return true;
        else if (token != ">" && token != ">>")
            throw invalid_argument(keyword + ": invalid argument");
        else {
            redirection = token;
            ss >> rdrfile;
            if (!regex_match(rdrfile, regex(path_file)))
                throw invalid_argument(keyword + ": invalid filename after '" + redirection + "'");
        }

        if (!ss.eof())
            throw invalid_argument(keyword + ": too many arguments");

        return true;
    }

    void execute() override {
        // pass
    }
};