#pragma once

#include <iostream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class rmdir_CMD : public COMMAND
{
private:

    vector<fs::path> directory;

public:
    rmdir_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "rmdir"

        if (ss.eof())
            throw invalid_argument(keyword + ": expected a directory"); // only "rmdir"

        while (ss >> token) {
            if (regex_match(token, regex(path_dir)))
                directory.push_back(token);
            else throw invalid_argument(keyword + ": '" + token + "': invalid directory");
        }

        return true;
    }

    void execute() override {

        for (auto dir : directory) {

            // get removing-directory validated location
            fs::path dir_location = get_location(dir);

            // check whether you're stupid enough to be removing the directory where you currently are
            if (dir_location == noob.current_directory)
                throw invalid_argument(keyword + ": cannot remove current directory");
                
            if (!fs::exists(dir_location))
                throw invalid_argument(keyword + ": '" + dir.string() + "': no such directory");
                
            try {
                fs::remove(dir_location);
            }
            catch (...) {
                throw invalid_argument(keyword + ": '" + dir.string() + "': couldn't remove (directory is not empty)");
            }
        }
    }
};