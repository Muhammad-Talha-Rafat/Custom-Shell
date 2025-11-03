#pragma once

#include <iostream>
#include <vector>

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

            fs::path dir_parent;
            try {
                // try to get parent directory
                dir_parent = fs::canonical(noob.current_directory / dir.parent_path());
            }
            catch(...) {
                throw invalid_argument(keyword + ": '" + dir.parent_path().string() + "': bad parent path");
            }

            // throw error if given directory location leads beyond Playground
            if (dir_parent.lexically_relative(noob.home_directory).string().rfind("..", 0) == 0)
                throw invalid_argument(keyword + ": (out of bounds) access denied");    
                
            fs::path dir_location = dir_parent / dir.filename();

            if (fs::exists(dir_location))
                throw invalid_argument(keyword + ": '" + dir.string() + "': directory already exists");
            else if (!fs::create_directory(dir_location))
                throw invalid_argument(keyword + ": '" + dir.string() + "': couldn't create");
        }
    }
};