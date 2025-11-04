#pragma once

#include <iostream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class cat_CMD : public COMMAND
{
private:

    fs::path filename;
    string redirection;
    fs::path rdrfile;

public:

    cat_CMD(const string& token) {
        keyword = token;
        filename = "";
        redirection = "";
        rdrfile = "";
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "cat"

        if (ss.eof()) throw invalid_argument(keyword + ": expected a filename");

        if (ss >> token) {
            if (token == "<") ss >> token; // ignore "<" 
            if (token[0] == '-') throw invalid_argument(keyword + ": '" + token + "': no options supported");
            else if (validate_file_path(token))
                filename = token;
            else throw invalid_argument(keyword + ": '" + token + "': expected a filename");
        }

        if (ss >> token) {
            if (token == ">" || token == ">>")
                redirection = token;
            else throw invalid_argument(keyword + ": '" + token + "': expected a forward redirection");

            if (!(ss >> token))
                throw invalid_argument(keyword + ": '" + token + "': expected a filename");
            else if (validate_file_path(token))
                rdrfile = token;
            else throw invalid_argument(keyword + ": '" + token + "': invalid filename");
        }

        if (ss >> token) throw invalid_argument(keyword + ": '" + token + "': too many arguments");

        return true;
    }


    void execute() override {
        
        fs::path file_location = get_location(filename);

        if (fs::exists(file_location.filename()))
            throw invalid_argument(keyword + ": '" + file_location.filename().string() + "': no such file");

        ifstream file(file_location);
        string line;
        stringstream output;

        while (getline(file, line))
            output << line << endl;
        file.close();

        cout << output.str();

        if (!redirection.empty()) {
            fs::path rdrfile_location = get_location(rdrfile);

            if (redirection == ">") ofstream(rdrfile_location) << output.str();
            else ofstream(rdrfile_location, ios::app) << output.str();
        }
    }
};