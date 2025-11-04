#pragma once

#include <iostream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class cp_CMD : public COMMAND
{
private:

    fs::path source;
    fs::path destination;
    bool _r;

public:

    cp_CMD(const string& token) {
        keyword = token;
        source = "";
        destination = "";
        _r = false;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "cp"

        if (!(ss >> token))
            throw invalid_argument(keyword + ": expected a file or directory");

        if (validate_file_path(token)) {
            source = token;
            if (!(ss >> destination))
                throw invalid_argument(keyword + ": expected a destination");
            else if (!validate_file_path(destination) && !validate_dir_path(destination))
                throw invalid_argument(keyword + ": '" + destination.string() + "': invalid destination");
        }
        else if (regex_match(token, regex(path_dir)))
            throw invalid_argument(keyword + ": missing '-r' option");
        else if (token == "-r") {
            _r = true;
            if (!(ss >> source))
                throw invalid_argument(keyword + ": expected a source directory");
            else if (!validate_dir_path(source))
                throw invalid_argument(keyword + ": '" + source.string() + "': invalid source");
            if (!(ss >> destination))
                throw invalid_argument(keyword + ": expected a destination");
            else if (!validate_dir_path(destination))
                throw invalid_argument(keyword + ": '" + destination.string() + "': invalid destination");
        }
        else if (token[0] == '-')
            throw invalid_argument(keyword + ": '" + token + "': invalid option");
        else throw invalid_argument(keyword + ": invalid format");

        if (ss >> token) throw invalid_argument(keyword + ": '" + token + "': too many arguments");

        return true;
    }

    void execute() override {

        // are you trying to create something like *.txt?
        if (source.filename().string()[0] == '*')
            throw invalid_argument(keyword + ": '" + source.filename().string() + "': invalid filename");
        if (destination.filename().string()[0] == '*')
            throw invalid_argument(keyword + ": '" + destination.filename().string() + "': invalid filename");

        // get validated paths
        fs::path source_location = get_location(source);
        fs::path destination_location = get_location(destination);        

        if (!fs::exists(source_location))
            throw invalid_argument(keyword + ": '" + source.string() + "': no such file or directory");

        if (_r) {
            fs::copy(source_location, destination_location, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        }
        else if (fs::is_regular_file(source_location)) {
            if (fs::is_directory(destination_location)) // are you copying file to a folder?
                destination_location /= source_location.filename();
            fs::copy_file(source_location, destination_location, fs::copy_options::overwrite_existing);
        }
        else throw invalid_argument(keyword + ": (error) operation couldn't perform");

    }
};