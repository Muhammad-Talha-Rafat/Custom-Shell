#pragma once

#include <iostream>
#include <vector>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class find_CMD : public COMMAND
{
private:

    string directory;
    struct _name {
        bool _check = false;
        string _pattern = "";
    } name;
    struct _type {
        bool _check = false;
        char _type = '\0';
    } type;
    struct _size {
        bool _check = false;
        char _sign = '\0';
        int _integer = 0;
        char _unit = '\0';
    } size;
    string filename;
    string redirection;
    string rdrfile;

public:

    find_CMD(const string& token) {
        keyword = token;
        directory = ".";
        filename = "";
        redirection = "";
        rdrfile = "";
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "find"

        if (!(ss >> token))
            throw invalid_argument(keyword + ": invalid format");

        if (!regex_match(token, regex(path_dir)))
            throw invalid_argument(keyword + ": '" + token + "': invalid directory");

        if (!(ss >> token))
            return true;

        auto check_flag = [&](bool& check, const string& option) {
            if (check)
                throw invalid_argument(keyword + ": '" + option + "': cannot have multiple occurrences of an option");
            check = true;
        };

        while (token[0] == '-' && !ss.eof()) {
            if (token == "-name") {
                check_flag(name._check, token);
                ss >> name._pattern;
                string pattern = "\"([a-zA-Z][a-zA-Z0-9_]*|\\*)\\.[a-zA-Z]+\""; // regex for name argument
                if (!regex_match(name._pattern, regex(pattern)))
                    throw invalid_argument(keyword + ": '" + name._pattern + "': invalid '-name' argument");
            }
            else if (token == "-type") {
                check_flag(type._check, token);
                ss >> type._type;
                if (type._type != 'f' && type._type != 'd')
                    throw invalid_argument(keyword + ": '" + string(1, type._type) + "': invalid '-type' argument");
            }
            else if (token == "-size") {
                check_flag(size._check, token);
                ss >> token;
                string pattern = "[+-]?[0-9]+[CKM]"; // regex for size argument
                if (!regex_match(token, regex(pattern)))
                    throw invalid_argument(keyword + ": '" + token + "': invalid '-size' argument");
                if (token[0] == '+' || token[0] == '-') size._sign = token[0];
                size._integer = stoi(token.substr(size._sign ? 1 : 0, token.length() - (size._sign ? 2 : 1)));
                size._unit = token[token.length() - 1];
            }
            else throw invalid_argument(keyword + ": '" + token + "': option not supported");

            if (!(ss >> token))
                return true;
        }

        if (token == "<") {
            if (!(ss >> filename))
                throw invalid_argument(keyword + ": expected a filename");
            else if (!regex_match(filename, regex(path_file)))
                throw invalid_argument(keyword + ": '" + filename + "': invalid filename");
            if (!(ss >> token))
                return true;
            if (token == ">" || token == ">>") {
                if (!(ss >> rdrfile))
                    throw invalid_argument(keyword + ": missing redirected filename");
                else if (!regex_match(rdrfile, regex(path_file)))
                    throw invalid_argument(keyword + ": '" + rdrfile + "': invalid redirected filename");
            }
            else throw invalid_argument(keyword + ": '" + token + "': invalid redirection operator");
        }
        else if (token == ">" || token == ">>") {
            if (!(ss >> rdrfile))
                throw invalid_argument(keyword + ": missing redirected filename");
            else if (!regex_match(rdrfile, regex(path_file)))
                throw invalid_argument(keyword + ": '" + rdrfile + "': invalid redirected filename");
        }
        else throw invalid_argument(keyword + ": '" + token + "': invalid format");

        if (!ss.eof())
            throw invalid_argument(keyword + ": too many arguments");

        return true;
    }

    void execute() override {
        // pass
    }
};