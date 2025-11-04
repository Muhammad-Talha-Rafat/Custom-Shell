#pragma once

#include <iostream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class mkdir_CMD : public COMMAND
{
private:

    vector<fs::path> directory;

public:
    mkdir_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "mkdir"

        if (ss.eof())
            throw invalid_argument(keyword + ": expected a directory"); // only "mkdir"

        while (ss >> token) {
            if (regex_match(token, regex(path_dir)))
                directory.push_back(token);
            else throw invalid_argument(keyword + ": '" + token + "': invalid directory");
        }

        return true;
    }

    void execute() override {

        for (auto dir : directory) {

            // get validated directory location
            fs::path dir_location = get_location(dir);

            if (fs::exists(dir_location))
                throw invalid_argument(keyword + ": '" + dir.string() + "': directory already exists");
            else if (!fs::create_directory(dir_location))
                throw invalid_argument(keyword + ": '" + dir.string() + "': couldn't create");
        }
    }
};