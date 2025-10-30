#pragma once

#include <iostream>
#include "shell.h"


using namespace std;
using namespace SHELL;

class ls_CMD : public COMMAND
{
public:
    ls_CMD(const string& cmd) {
        keyword = "ls";
        if (!regex_match(cmd, RULE.at("ls")))
            throw invalid_argument(keyword + ": invalid format");
    }

    bool validate(const string& cmd) override {
        return true;
    }

    void execute() override {
        cout << "Executing ls...\n";
    }
};