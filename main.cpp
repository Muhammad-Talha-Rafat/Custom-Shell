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



/*

find .
find .          -name   "*.txt"
find .          -iname  "*.txt"
find .          -type   f
find .          -type   d
find .          -size   +10K
find .          -size   -5M
find .          -size   100C

find .          -name   "*.txt" -type f
find .          -iname  "*.txt" -type f
find .          -name   "*.txt" -type d
find .          -iname  "*.txt" -type d
find .          -name   "*.txt" -size +10k
find .          -iname  "*.txt" -size +10k
find .          -type   f -size +10k
find .          -type   d -size -1M
find .          -name   "*.txt" -type f -size +10k
find .          -iname  "*.txt" -type d -size -1M

find folder
find folder     -name   "*.py"
find folder     -iname  "*.py"
find folder     -type   f
find folder     -type   d
find folder     -size   +1M
find folder     -name   "*.py" -type f
find folder     -iname  "*.py" -type f
find folder     -name   "*.py" -size +1M
find folder     -type   f -size +1M
find folder     -name   "*.py" -type f -size +1M

find .      >                       result.txt
find .      >>                      result.txt
find .          -name   "*.txt" > result.txt
find .          -iname  "*.txt" > result.txt
find .          -type   f > result.txt
find .          -size   +10K > result.txt
find .          -name   "*.txt" -type f > result.txt
find .          -iname  "*.txt" -type d > result.txt
find .          -name   "*.txt" -type f -size +10k > result.txt
find .          -iname  "*.txt" -type d -size -1M > result.txt

find .      >>              result.txt
find .          -name   "*.txt" >> result.txt
find .          -iname  "*.txt" >> result.txt
find .          -type   f >> result.txt
find .          -size   +10k >> result.txt
find .          -name   "*.txt" -type f >> result.txt
find .          -iname  "*.txt" -type d >> result.txt
find .          -name   "*.txt" -type f -size +10k >> result.txt
find .          -iname  "*.txt" -type d -size -1M >> result.txt

find .      <               input.txt
find .          -name   "*.txt" < input.txt
find .          -iname  "*.txt" < input.txt
find .          -type   f < input.txt
find .          -size   +10k < input.txt
find .          -name   "*.txt" -type f < input.txt
find .          -iname  "*.txt" -type d < input.txt
find .          -name   "*.txt" -type f -size +10k < input.txt
find .          -iname  "*.txt" -type d -size -1M < input.txt

find .          -name   "*.txt" < input.txt > result.txt
find .          -iname  "*.txt" < input.txt >> result.txt
find .          -type   f < input.txt > result.txt
find .          -size   +10k < input.txt >> result.txt
find .          -name   "*.txt" -type f -size +10k < input.txt > result.txt
find .          -iname  "*.txt" -type d -size -1M < input.txt >> result.txt

*/