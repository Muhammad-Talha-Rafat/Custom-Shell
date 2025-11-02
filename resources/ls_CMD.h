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
            if (!regex_match(token, regex(path_dir)))
                throw invalid_argument(keyword + ":  '" + token + "': invalid directory");
            directory = token;
            if (!(ss >> token)) 
                return true; // command ended after "< folder"
        }
        
        if (directory.empty() && regex_match(token, regex(path_dir))) {
            directory = token;
            if (!(ss >> token))
                return true; // command ended after "folder"
        }
        
        if (token == ">" || token == ">>") {
            redirection = token;
            if (!(ss >> rdrfile))
                throw invalid_argument(keyword + ": expected a filename after '" + redirection + "'");
            if (!regex_match(rdrfile.string(), regex(path_file)))
                throw invalid_argument(keyword + ": '" + rdrfile.string() + "': invalid filename");
            if (ss >> token)
                throw invalid_argument(keyword + ": too many arguments");
            return true; // command ended after ">/>> filename"
        }

        throw invalid_argument(keyword + ": '" + token + "': unexpected token");
    }

    void execute() override {

        fs::path canonical_path = fs::canonical(noob.current_directory / directory);
        stringstream output;

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

        if (!rdrfile.empty()) {
            fs::path file_location = noob.current_directory / rdrfile;
            fs::path file_folder = file_location.parent_path();

            if (file_folder.empty())
                file_folder = noob.current_directory;

            if (fs::exists(file_folder)) {
                fs::path canonical_path = fs::canonical(file_folder);
                if (redirection == ">") ofstream(file_location) << output.str();
                else ofstream(file_location, ios::app) << output.str();
            }
            else throw invalid_argument("ls: '" + rdrfile.string() + "': invalid path");
        }
    }
};