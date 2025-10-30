#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <regex>

using namespace std;

namespace SHELL {
    extern const unordered_set<string> KEYWORDS;
    extern const unordered_map<string, unordered_set<string>> OPTIONS;
    extern const string path_dir;
    extern const string path_file;
    extern const unordered_map<string, regex> RULE;
}
