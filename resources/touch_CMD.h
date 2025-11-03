#pragma once

#include <iostream>
#include <vector>
#include <chrono>

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

            // get the parent directory
            fs::path file_parent;
            try {
                // try to get parent directory
                file_parent = fs::canonical(noob.current_directory / file.parent_path());
            }
            catch(...) {
                throw invalid_argument(keyword + ": '" + file.parent_path().string() + "': bad parent path");
            }

            fs::path relative_path = file_parent.lexically_relative(noob.home_directory);
            // throw error if processing location leads beyond Playground
            if (relative_path.string().rfind("..", 0) == 0)
                throw invalid_argument(keyword + ": (out of bounds) access denied");

            // move from current location to file location
            fs::path file_location = noob.current_directory / file;

            if (fs::exists(file_location))
                fs::last_write_time(file_location, fs::file_time_type::clock::now());
            else {
                ofstream file(file_location);
                file.close();
            }
        }
    }
};