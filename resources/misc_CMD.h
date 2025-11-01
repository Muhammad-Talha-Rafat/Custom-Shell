#pragma once

#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>

#include "command.h"
#include "shell.h"

using namespace std;
using namespace SHELL;

class misc_CMD : public COMMAND
{
public:

    misc_CMD(const string& token) {
        keyword = token;
    }

    bool validate(const string& cmd) override {
        stringstream ss(cmd);
        string token;
        ss >> token; // consume keyword

        if (!ss.eof())
            throw invalid_argument(keyword + ": too many arguments");

        return true;
    }
};

class pwd_MISC : public misc_CMD
{
public:

    pwd_MISC() : misc_CMD("pwd") {}

    void execute() override {
        cout << "pwd..." << endl;
    }
};

class date_MISC : public misc_CMD
{
public:

    date_MISC() : misc_CMD("date") {}

    void execute() override {
        time_t now = time(nullptr);
        tm* local = localtime(&now);
        cout << put_time(local, "%Y-%m-%d") << endl;
    }
};

class time_MISC : public misc_CMD
{
public:

    time_MISC() : misc_CMD("time") {}

    void execute() override {
        time_t now = time(nullptr);
        tm* local = localtime(&now);
        cout << put_time(local, "%H:%M:%S") << endl;
    }
};

class help_MISC : public misc_CMD
{
public:

    help_MISC() : misc_CMD("help") {}

    void execute() override {
        ifstream file("help.txt");
        cout << endl;
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(':');
            string cmd = line.substr(0, pos);
            string desc = line.substr(pos + 1);
            cmd.erase(cmd.find_last_not_of(" \t") + 1);
            desc.erase(0, desc.find_first_not_of(" \t"));
            cout << left << setw(20) << cmd << desc << '\n';
        }
        cout << endl;
        file.close();
    }
};

class history_MISC : public misc_CMD
{
public:

    history_MISC() : misc_CMD("history") {}

    void execute() override {
        ifstream file("history.log");
        string line;
        while (getline(file, line)) {
            size_t pos = line.find('\t');
            if (pos == string::npos) continue; 

            string timestamp = line.substr(0, pos);
            string cmd = line.substr(pos + 1);

            timestamp.erase(timestamp.find_last_not_of(" \t") + 1);
            cmd.erase(0, cmd.find_first_not_of(" \t"));

            cout << "\033[0;32m" << left << setw(20) << timestamp << "\033[0m" << ' ' << cmd << '\n';
        }
        file.close();
    }
};