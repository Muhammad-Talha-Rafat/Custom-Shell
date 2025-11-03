#pragma once

#include <iostream>
#include <vector>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class rm_CMD : public COMMAND
{
private:

    vector<fs::path> filenames;
    vector<fs::path> directories;
    bool _r;

public:
    rm_CMD(const string& token) {
        keyword = token;
        _r = false;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "rm"

        if (!(ss >> token)) // only "rm"
            throw invalid_argument(keyword + ": expected a filename or directory");

        if (token == "-r") {
            _r = true;
            if (!(ss >> token)) // only "rm -r"
                throw invalid_argument(keyword + ": expected a directory");
        }
        else if (token[0] == '-')
            throw invalid_argument(keyword + ": '" + token + "': invalid option");

        if (_r) do {
            if (regex_match(token, regex(path_dir)))
                directories.push_back(token);
            else throw invalid_argument(keyword + ": '" + token + "': invalid directory");
        } while (ss >> token);
        else do {
            if (regex_match(token, regex(path_file)) || regex_match(token, regex("\\*\\.[A-Za-z]+")))
                filenames.push_back(token);
            else throw invalid_argument(keyword + ": '" + token + "': invalid filename/path");
        } while (ss >> token);

        return true;
    }

    void execute() override {

        auto objects = _r ? directories : filenames;

        for (const auto& object : objects) {
            fs::path object_parent;
            try {
                // try to get parent directory
                object_parent = fs::canonical(noob.current_directory / object.parent_path());
            }
            catch(...) {
                throw invalid_argument(keyword + ": '" + object.parent_path().string() + "': bad parent path");
            }

            fs::path relative_path = object_parent.lexically_relative(noob.home_directory);
            // throw error if object location leads beyond Playground
            if (relative_path.string().rfind("..", 0) == 0)
                throw invalid_argument(keyword + ": (out of bounds) access denied");

            // get removing object location
            fs::path object_location = object_parent / object.filename();

            // check whether you're foolish enough to be removing the directory where you currently are
            if (object_location == noob.current_directory)
                throw invalid_argument(keyword + ": cannot remove current directory");

            if (object.filename().string()[0] == '*') {
                // remove all extension-given files
                string extension = object.extension().string(); // extract extension
                // go relatvely from current location to object parent directory
                fs::path updated_path = noob.current_directory / object.parent_path();
                for (const auto& file : fs::directory_iterator(updated_path))
                    if (file.path().extension() == extension)
                        fs::remove(file.path());
            }
            else {
                if (!fs::exists(object_location))
                    throw invalid_argument(keyword + ": '" + object.string() + "': no such " + (_r ? "directory" : "file"));   
                                        
                if (_r) fs::remove_all(object_location);
                else fs::remove(object_location);
            }
        }

    }
};