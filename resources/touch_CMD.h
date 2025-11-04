#pragma once

#include <iostream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class touch_CMD : public COMMAND
{
private:

    vector<fs::path> filenames;

public:

    touch_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "touch"

        if (!(ss >> token))
            throw invalid_argument(keyword + ": missing file name");

        do {
            if (validate_file_path(token))
                filenames.push_back(token);
            else throw invalid_argument(keyword + ": '" + token + "': expected a filename");
        } while (ss >> token);

        return true;
    }

    void execute() override {
        
        for (auto file : filenames) {

            // are you trying to create something like *.txt?
            if (file.filename().string()[0] == '*')
                throw invalid_argument(keyword + ": '" + file.filename().string() + "': invalid filename");

            // get validated file location
            fs::path file_location = get_location(file);

            if (fs::exists(file_location))
                fs::last_write_time(file_location, fs::file_time_type::clock::now());
            else {
                ofstream file(file_location);
                file.close();
            }
        }
    }
};