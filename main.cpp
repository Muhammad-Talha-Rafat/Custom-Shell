#include <iostream>
#include <vector>
#include <sstream>
#include "shell.cpp"
using namespace std;
using namespace SHELL;

class COMMAND
{
private:

    string keyword;
    vector<string> options;
    vector<string> arguments;

public:

    COMMAND() {
        this->keyword.clear();
        this->options.clear();
        this->arguments.clear();
    }

    void print() const {
        cout << "Command: " << this->keyword << endl;
        cout << "Options: ";
        for (auto& opt : options) cout << opt << " ";
        cout << endl << "Arguments: ";
        for (auto& arg : arguments) cout << arg << " ";
        cout << endl;
    }

    void tokenize(const string& cmd) {
        stringstream ss(cmd);
        string token;
        vector<string> tokens;


        while (ss >> token)
            tokens.push_back(token);

        if (tokens.empty()) return;

        keyword = tokens[0];

        for (size_t i = 1; i < tokens.size(); i++) {
            if (tokens[i].size() > 0 && tokens[i][0] == '-') {
                if (tokens[i][0] == '-' && tokens[i][1] >= '0' && tokens[i][1] <= '9') // special case for negative numbers
                    arguments.push_back(tokens[i]);
                else options.push_back(tokens[i]);
            }
            else if (tokens[i].size() > 0)
                arguments.push_back(tokens[i]);
            else break;
        }

        bool matched = false;
        for (auto rule: RULES) {
            if (regex_match(cmd, rule.second)) {
                matched = true;
                break;
            }
        }
        if (!matched) throw invalid_argument(keyword + ": invalid command");
    }

    void validation() {
        if (KEYWORDS.find(keyword) == KEYWORDS.end())
            throw invalid_argument(keyword + ": invalid command");

        if (OPTIONS.find(keyword) != OPTIONS.end()) {
            for (const auto& opt : options)
                if (OPTIONS.at(keyword).find(opt) == OPTIONS.at(keyword).end())
                    throw invalid_argument("invalid option '" + opt + "' for command '" + keyword + "'");
        }
        else if (!options.empty())
            throw invalid_argument("command '" + keyword + "' does not accept options");

    }


};

int main() {
    int count = 0;

    while (1) {
        string command;
        cout << "Playground $ ";
        getline(cin, command);

        COMMAND cmd;
        try {
            cmd.tokenize(command);
            cmd.validation();
        } catch (const invalid_argument& e) {
            cerr << e.what() << endl;
        }
        // cmd.print();
    }
    return 0;
}
