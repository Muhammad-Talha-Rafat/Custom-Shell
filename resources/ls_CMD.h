#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class ls_CMD : public COMMAND
{
private:

    bool _l;
    fs::path directory;
    string redirection;
    fs::path rdrfile;

public:

    ls_CMD(const string& token) {
        keyword = token;
        _l = false;
        directory = "";
        redirection = "";
        rdrfile = "";
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "ls"
        
        if (ss >> token) {
            if (token == "-l") {
                _l = true;
                if (!(ss >> token))
                    return true; // only "ls -l"
            }
            else if (token[0] == '-')
                throw invalid_argument(keyword + ": '" + token + "': option not supported");
        }
        else return true; // only "ls"
        
        if (token == "<") {
            if (!(ss >> token)) // ignore "<"
                throw invalid_argument(keyword + ": expected a directory after '<'");
            if (!validate_dir_path(token))
                throw invalid_argument(keyword + ":  '" + token + "': invalid directory");
            directory = token;
            if (!(ss >> token)) 
                return true; // command ended after "< folder"
        }
        
        if (directory.empty() && validate_dir_path(token)) {
            directory = token;
            if (!(ss >> token))
                return true; // command ended after "folder"
        }
        
        if (token == ">" || token == ">>") {
            redirection = token;
            if (!(ss >> rdrfile))
                throw invalid_argument(keyword + ": expected a filename after '" + redirection + "'");
            if (!validate_file_path(rdrfile))
                throw invalid_argument(keyword + ": '" + rdrfile.string() + "': invalid filename");
            if (ss >> token)
                throw invalid_argument(keyword + ": too many arguments");
            return true; // command ended after ">/>> filename"
        }

        throw invalid_argument(keyword + ": '" + token + "': unexpected argument");
    }

    void execute() override {

        stringstream output;

        fs::path canonical_path = fs::canonical(noob.current_directory / directory);

        fs::path relative_path = canonical_path.lexically_relative(noob.home_directory);
        // throw error if current location leads beyond Playground
        if (relative_path.string().rfind("..", 0) == 0)
            throw invalid_argument(keyword + ": (out of bounds) access denied");

        for (const auto& entry : fs::directory_iterator(canonical_path)) {
            if (fs::is_regular_file(entry.path())) {
                if (_l) {
                    string filename = entry.path().filename().string();

                    auto file_time = fs::last_write_time(entry);
                    auto sctp = chrono::time_point_cast<std::chrono::system_clock::duration>(
                        file_time - fs::file_time_type::clock::now() + std::chrono::system_clock::now()
                    );
                    time_t system_time = chrono::system_clock::to_time_t(sctp); // get file timestamp

                    auto size = fs::file_size(entry.path()); // get file size

                    cout << "\033[2;32m"
                        << put_time(localtime(&system_time), "%Y-%m-%d %H:%M:%S")
                        << setw(6) << size << " B"
                        << setw(7) << "\033[0m"
                        << filename << endl; // print on terminal

                    output << put_time(localtime(&system_time), "%Y-%m-%d %H:%M:%S")
                        << '\t' << size << " B"
                        << '\t' << filename << endl; // redirect on file
                }
                else {
                    cout << "\033[0;37m" << entry.path().filename().string() << "\033[0m" << endl;
                    output << entry.path().filename().string() << endl;
                }
            }
        }

        if (!redirection.empty()) {

            // are you trying to create something like *.txt?
            if (rdrfile.filename().string()[0] == '*')
                throw invalid_argument(keyword + ": '" + rdrfile.filename().string() + "': invalid filename");

            // get the parent directory
            fs::path file_parent;
            try {
                // try to get parent directory
                file_parent = fs::canonical(noob.current_directory / rdrfile.parent_path());
            }
            catch(...) {
                throw invalid_argument(keyword + ": '" + rdrfile.parent_path().string() + "': bad parent path");
            }

            // throw error if processing location leads beyond Playground
            if (file_parent.lexically_relative(noob.home_directory).string().rfind("..", 0) == 0)
                throw invalid_argument(keyword + ": (out of bounds) couldn't redirect");

            // move from current location to file location
            fs::path file_location = noob.current_directory / rdrfile;


            if (redirection == ">") ofstream(file_location) << output.str();
            else ofstream(file_location, ios::app) << output.str();
        }
    }
};