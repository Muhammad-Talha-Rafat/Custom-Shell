#pragma once

#include <iostream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class echo_CMD : public COMMAND
{
private:

    vector<string> messages;
    string redirection;
    fs::path rdrfile;

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
                if (messages.empty()) throw invalid_argument(keyword + ": expected some text before redirecting");
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
                messages.push_back(literal);
            }
            else throw invalid_argument(keyword + ": '" + token + "': expected some text instead");
        }

        if (messages.empty() && ss.eof())
            throw invalid_argument(keyword + ": expected some text after '" + token + "'");
        else if (ss.eof())
            return true;
        else if (token != ">" && token != ">>")
            throw invalid_argument(keyword + ": invalid argument");
        else {
            redirection = token;
            ss >> rdrfile;
            if (!validate_file_path(rdrfile))
                throw invalid_argument(keyword + ": invalid filename after '" + redirection + "'");
        }

        if (ss >> token) throw invalid_argument(keyword + ": '" + token + "': too many arguments");

        return true;
    }

    void execute() override {

        stringstream output;

        for (auto message : messages)
            output << message.substr(1, message.size() - 2) << endl;

        cout << output.str();

        if (!redirection.empty()) {

            // are you trying to create something like *.txt?
            if (rdrfile.filename().string()[0] == '*')
                throw invalid_argument(keyword + ": '" + rdrfile.filename().string() + "': invalid filename");

            // get validated file location
            fs::path file_location = get_location(rdrfile);

            if (redirection == ">") ofstream(file_location) << output.str();
            else ofstream(file_location, ios::app) << output.str();
        }
    }
};