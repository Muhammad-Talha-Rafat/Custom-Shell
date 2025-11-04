#pragma once

#include <iostream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class head_CMD : public COMMAND
{
private:

    fs::path filename;
    char option;
    size_t size;
    string redirection;
    fs::path rdrfile;

public:

    head_CMD(const string& token) {
        keyword = token;
        filename = "";
        option = '\0';
        size = 5;
        redirection = "";
        rdrfile = "";
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "head"

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

        if (validate_file_path(token)) {
            filename = token;
            if (!(ss >> token)) return true;
            if (token != ">" && token != ">>")
                throw invalid_argument(keyword + ": '" + token + "': expected a forward redirection");
            redirection = token;
            if(!(ss >> token))
                throw invalid_argument(keyword + ": expected a filename");
            else if (validate_file_path(token))
                rdrfile = token;
            else throw invalid_argument(keyword + ": '" + token + "': expected a filename");
        }
        else throw invalid_argument(keyword + ": '" + token + "': expected a filename");

        return true;
    }

    void execute() override {
        
        fs::path file_location = get_location(filename);

        ifstream file(file_location);
        stringstream output;

        if (option == 'c') {
            string buffer(size, '\0');
            file.read(&buffer[0], size);
            // trim if file size is less than requested size
            buffer.resize(file.gcount());
            output << buffer << endl;
        }
        else {
            string line;
            for (size_t i = 0; i < size && getline(file, line); i++)
                output << line << endl;
        }
        file.close();

        cout << output.str();

        if (!redirection.empty()) {
            fs::path rdrfile_location = get_location(rdrfile);

            if (redirection == ">") ofstream(rdrfile_location) << output.str();
            else ofstream(rdrfile_location, ios::app) << output.str();
        }
    }
};