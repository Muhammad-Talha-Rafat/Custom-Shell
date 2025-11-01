#pragma once

#include <iostream>
#include <vector>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class grep_CMD : public COMMAND
{
private:

    bool _i = false;
    bool _n = false;
    bool _w = false;
    bool _c = false;
    bool _l = false;
    bool _o = false;
    string text;
    string filename;
    string redirection;
    string rdrfile;

public:

    grep_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "grep"

        if (!(ss >> token))
            throw invalid_argument("grep: invalid format");

        auto check_flag = [&](bool& check, const string& option) {  // lambda function to detect multiple occurrences of an option
            if (check)
                throw invalid_argument("grep: '" + option + "': cannot have multiple occurrences of an option");
            check = true;
        };

        while (token[0] == '-' && !ss.eof()) {
            if (token == "-i") check_flag(_i, token);
            else if (token == "-n") check_flag(_n, token);
            else if (token == "-w") check_flag(_w, token);
            else if (token == "-c") check_flag(_c, token);
            else if (token == "-l") check_flag(_l, token);
            else if (token == "-o") check_flag(_o, token);
            else throw invalid_argument("grep: '" + token + "': option not supported");
            ss >> token;
        }

        if (token[0] == '"') { 
            text = token;
            while (token[token.length() - 1] != '"') {
                if (ss.eof())                                                       //  ends without running if there's only one literal,
                    throw invalid_argument("grep: unexpected end to the string");   //  otherwise keeps on consuming tokens until it either
                ss >> token;                                                        //  finds a token ending with ", or the command ends.
                text += " " + token;                                                //  literal can be "text", "more text" or "even more text"
            }
        }
        else throw invalid_argument("grep: '" + token + "': expected some text instead");

        if (!(ss >> token))
            throw invalid_argument("grep: expected a file name");


        if (token == "<")
            ss >> token; // ignore "<"

        if (!regex_match(token, regex(path_file)))
            throw invalid_argument("grep: '" + token + "': invalid file name");

        if (ss.eof()) return true; // grep [options] [text] [file] only
        else { // grep [options] [text] [file] [redirected file]
            ss >> token;
            if (token != ">" && token != ">>")
                throw invalid_argument("grep: '" + token + "': expected a forward redirection");
            redirection = token;
            if (!(ss >> token))
                throw invalid_argument("grep: missing file name");
            else if (!regex_match(token, regex(path_file)))
                throw invalid_argument("grep: '" + token + "': invalid file name");
            else rdrfile = token;
        }

        if (!(ss.eof()))
            throw invalid_argument("grep: too many arguments");

        return true;
    }

    void execute() override {
        // pass
    }
};