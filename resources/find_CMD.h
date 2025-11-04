#pragma once

#include <iostream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class find_CMD : public COMMAND
{
private:

    fs::path directory;
    struct _name {
        bool _check = false;
        string _pattern = "";
    } name;
    struct _type {
        bool _check = false;
        char _type = '\0';
    } type;
    struct _size {
        bool _check = false;
        char _sign = '\0';
        int _integer = 0;
        char _unit = '\0';
    } size;
    string redirection;
    fs::path rdrfile;

public:

    find_CMD(const string& token) {
        keyword = token;
        directory = "";
        redirection = "";
        rdrfile = "";
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume "find"

        if (!(ss >> token))
            throw invalid_argument(keyword + ": invalid format");

        if (!validate_dir_path(token))
            throw invalid_argument(keyword + ": '" + token + "': invalid directory");

        directory = token;

        if (!(ss >> token))
            return true;

        auto check_flag = [&](bool& check, const string& option) {
            if (check)
                throw invalid_argument(keyword + ": '" + option + "': cannot have multiple occurrences of an option");
            check = true;
        };

        while (token[0] == '-' && !ss.eof()) {
            if (token == "-name") {
                check_flag(name._check, token);
                ss >> name._pattern;
                string pattern = "\"([a-zA-Z][a-zA-Z0-9_]*|\\*)(\\.[a-zA-Z]+)?\""; // regex for name argument
                if (!regex_match(name._pattern, regex(pattern)))
                    throw invalid_argument(keyword + ": '" + name._pattern + "': invalid '-name' argument");
            }
            else if (token == "-type") {
                check_flag(type._check, token);
                ss >> type._type;
                if (type._type != 'f' && type._type != 'd')
                    throw invalid_argument(keyword + ": '" + string(1, type._type) + "': invalid '-type' argument");
            }
            else if (token == "-size") {
                check_flag(size._check, token);
                ss >> token;
                string pattern = "[+-]?[0-9]+[CKM]"; // regex for size argument
                if (!regex_match(token, regex(pattern)))
                    throw invalid_argument(keyword + ": '" + token + "': invalid '-size' argument");
                if (token[0] == '+' || token[0] == '-') size._sign = token[0];
                size._integer = stoi(token.substr(size._sign ? 1 : 0, token.length() - (size._sign ? 2 : 1)));
                size._unit = token[token.length() - 1];
            }
            else throw invalid_argument(keyword + ": '" + token + "': option not supported");

            if (!(ss >> token))
                return true;
        }

        if (token == ">" || token == ">>") {
            redirection = token;
            if (!(ss >> rdrfile))
                throw invalid_argument(keyword + ": missing redirected filename");
            else if (!validate_file_path(rdrfile))
                throw invalid_argument(keyword + ": '" + rdrfile.string() + "': invalid redirected filename");
        }
        else throw invalid_argument(keyword + ": '" + token + "': invalid format");

        if (!ss.eof())
            throw invalid_argument(keyword + ": too many arguments");

        return true;
    }

    void execute() override {
        
        fs::path dir_location = get_location(directory);
        vector<fs::path> objects;

        for (auto object : fs::recursive_directory_iterator(dir_location))
            objects.push_back(object);

        if (name._check) {
            // get rid of quotes
            name._pattern = name._pattern.substr(1, name._pattern.size() - 2);

            auto object = objects.begin();
            while (object != objects.end()) {
                string fname = object->filename().string();
                bool keep = false;

                // work with globs: "*.extension"
                if (name._pattern.size() >= 2 && name._pattern[0] == '*') {
                    string extension = name._pattern.substr(1);
                    if (fname.size() >= extension.size() && fname.compare(fname.size() - extension.size(), extension.size(), extension) == 0)
                        keep = true;
                } 
                else if (fname == name._pattern)
                    keep = true; // full filename pattern

                if (keep) object++;
                else object = objects.erase(object);
            }
        }

        if (type._check) {
            auto object = objects.begin();
            while (object != objects.end()) {
                if (type._type == 'f' && !fs::is_regular_file(*object))
                    object = objects.erase(object);
                else if (type._type == 'd' && !fs::is_directory(*object))
                    object = objects.erase(object);
                else object++;
            }
        }

        if (size._check) {
            auto object = objects.begin();
            while (object != objects.end()) {
                if (!fs::is_regular_file(*object)) {
                    object = objects.erase(object);
                    continue;
                }

                auto file_size = fs::file_size(*object);

                long long threshold = size._integer;
                switch (size._unit) {
                    case 'C': break;
                    case 'K': threshold *= 1024; break;
                    case 'M': threshold *= 1024 * 1024; break;
                }

                bool remove = false;
                switch (size._sign) {
                    case '+': if (!(file_size > threshold)) remove = true; break;
                    case '-': if (!(file_size < threshold)) remove = true; break;
                    case '\0': if (!(file_size == threshold)) remove = true; break;
                    default: break;
                }

                if (remove) object = objects.erase(object);
                else object++;    
            }
        }

        stringstream output;
        for (auto object : objects) {
            fs::path relative_path = object.lexically_relative(noob.current_directory);
            output << relative_path.string() << endl;
        }

        cout << output.str();

        if (!redirection.empty()) {
            fs::path rdrfile_location = get_location(rdrfile);

            if (redirection == ">") ofstream(rdrfile_location) << output.str();
            else ofstream(rdrfile_location, ios::app) << output.str();
        }
    }
};