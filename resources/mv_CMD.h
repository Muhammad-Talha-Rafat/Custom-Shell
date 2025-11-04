#pragma once

#include <iostream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class mv_CMD : public COMMAND
{
private:

    fs::path source;
    fs::path destination;

public:

    mv_CMD(const string& token) {
        keyword = token;
        source = "";
        destination = "";
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string keyword;
        ss >> keyword; // consume "mv"

        if (!(ss >> source))
            throw invalid_argument(keyword + ": expected a file or directory");

        if (validate_file_path(source)) {
            if (!(ss >> destination))
                throw invalid_argument(keyword + ": expected a destination");
            else if (!validate_file_path(destination) && !validate_dir_path(destination))
                throw invalid_argument(keyword + ": '" + destination.string() + "': invalid destination");
        }
        else if (validate_dir_path(source)) {
            if (!(ss >> destination))
                throw invalid_argument(keyword + ": expected a destination");
            else if (!validate_dir_path(destination))
                throw invalid_argument(keyword + ": '" + destination.string() + "': expected a directory");
        }
        else {
            if (source.string()[0] == '-') throw invalid_argument("mv: no option supported");
            else throw invalid_argument(keyword + ": '" + source.string() + "': invalid source");
        }

        string token;
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

        // lets try renaming first
        error_code code;
        fs::rename(source_location, destination_location, code);
        if (!code) return;

        // renaming failed
        if (fs::is_directory(source_location) && fs::is_directory(destination_location)) {
            fs::copy(source_location, destination_location, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
            fs::remove_all(source_location);
        }
        else if (fs::is_regular_file(source_location)) {
            if (fs::is_directory(destination_location)) // are you copying file to a folder?
                destination_location /= source_location.filename();
            fs::copy_file(source_location, destination_location, fs::copy_options::overwrite_existing);
            fs::remove(source_location);
        }
        else throw invalid_argument(keyword + ": (error) copy operation couldn't perform");

    }
};