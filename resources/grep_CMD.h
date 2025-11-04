#pragma once

#include <iostream>
#include <string>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class grep_CMD : public COMMAND
{
private:

    bool _i;
    bool _n;
    bool _w;
    bool _c;
    string text;
    fs::path filename;
    string redirection;
    fs::path rdrfile;

public:

    grep_CMD(const string& token) {
        keyword = token;
        _i = false;
        _n = false;
        _w = false;
        _c = false;
        text = "";
        filename = "";
        redirection = "";
        rdrfile = "";
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "grep"

        if (!(ss >> token))
            throw invalid_argument(keyword + ": invalid format");

        auto check_flag = [&](bool& check, const string& option) {  // lambda function to detect multiple occurrences of an option
            if (check)
                throw invalid_argument(keyword + ": '" + option + "': cannot have multiple occurrences of an option");
            check = true;
        };

        while (token[0] == '-' && !ss.eof()) {
            if (token == "-i") check_flag(_i, token);
            else if (token == "-n") check_flag(_n, token);
            else if (token == "-w") check_flag(_w, token);
            else if (token == "-c") check_flag(_c, token);
            else throw invalid_argument(keyword + ": '" + token + "': option not supported");
            ss >> token;
        }

        if (token[0] == '"') { 
            text = token;
            while (token[token.length() - 1] != '"') {
                if (ss.eof())                                                           //  ends without running if there's only one literal,
                    throw invalid_argument(keyword + ": unexpected end to the string"); //  otherwise keeps on consuming tokens until it either
                ss >> token;                                                            //  finds a token ending with ", or the command ends.
                text += " " + token;                                                    //  literal can be "text", "more text" or "even more text"
            }
        }
        else throw invalid_argument(keyword + ": '" + token + "': expected some text instead");

        if (!(ss >> token))
            throw invalid_argument(keyword + ": expected a file name");


        if (token == "<")
            ss >> token; // ignore "<"

        if (!validate_file_path(token))
            throw invalid_argument(keyword + ": '" + token + "': invalid file name");

        filename = token;

        if (ss.eof()) return true; // grep [options] [text] [file] only
        else { // grep [options] [text] [file] [redirected file]
            ss >> token;
            if (token != ">" && token != ">>")
                throw invalid_argument(keyword + ": '" + token + "': expected a forward redirection");
            redirection = token;
            if (!(ss >> token))
                throw invalid_argument(keyword + ": missing file name");
            else if (!validate_file_path(token))
                throw invalid_argument(keyword + ": '" + token + "': invalid file name");
            else rdrfile = token;
        }

        if (!(ss.eof()))
            throw invalid_argument(keyword + ": too many arguments");

        return true;
    }

    void execute() override {
        fs::path file_location = get_location(filename);

        // get rid of quotes
        text = text.substr(1, text.size() - 2);

        ifstream file(file_location);

        string line;
        int linenumber = 0;
        int count = 0;
        stringstream output;

        // regex for -w option
        regex _w_pattern("\\b" + text + "\\b", _i ? regex_constants::icase : regex_constants::ECMAScript);

        while (getline(file, line)) {
            linenumber++;
            bool matched = false;

            if (_i) {
                string line_lower = line;
                string text_lower = text;
                transform(line_lower.begin(), line_lower.end(), line_lower.begin(), ::tolower);
                transform(text_lower.begin(), text_lower.end(), text_lower.begin(), ::tolower);

                if (line_lower.find(text_lower) != string::npos)
                    matched = true;
            }
            else if (line.find(text) != string::npos) matched = true;

            if (_w) {
                if (regex_search(line, _w_pattern)) matched = true;
                else matched = false;
            }

            if (matched) {
                count++;
                if (!_c) {
                    if (_n) output << linenumber << ":";
                    output << line << endl;
                }
            }
        }


        if (_c) output << count << endl;

        cout << output.str();

        if (!redirection.empty()) {
            fs::path rdrfile_location = get_location(rdrfile);

            if (redirection == ">") ofstream(rdrfile_location) << output.str();
            else ofstream(rdrfile_location, ios::app) << output.str();
        }
    }

};