#include "shell.h"

using namespace std;

namespace SHELL
{
    const unordered_set<string> KEYWORDS = {
        "ls", "pwd", "cd", "mkdir", "rmdir", "rm",
        "cp", "mv",
        "cat", "head", "tail",
        "touch", "echo",
        "date", "time", "clear", "history", "exit", "help",
        "grep", "find"
    };

    const unordered_map<string, unordered_set<string>> OPTIONS = {
        {"ls", {"-l"}},
        {"rm", {"-r"}},
        {"cp", {"-r"}},
        {"head", {"-n", "-c"}},
        {"tail", {"-n", "-c"}},
        {"grep", {"-i", "-n", "-w", "-c", "-l", "-o"}},
        {"find", {"-name", "-iname", "-type", "-size"}}
    };

    const string path_dir = R"((?:\.\./|\./|/)?(?:[A-Za-z_][A-Za-z0-9_]*|\.\.?)(?:/(?:[A-Za-z_][A-Za-z0-9_]*|\.\.?))*/?)";
    const string path_file = R"((?:(?:\.\./|\./|/)?(?:[A-Za-z_][A-Za-z0-9_]*|\.\.?)(?:/(?:[A-Za-z_][A-Za-z0-9_]*|\.\.?))*/)?(([A-Za-z][A-Za-z0-9_]*|\*))\.[A-Za-z]+)";

    static const regex dir_pattern(path_dir);
    static const regex file_pattern(path_file);

    const bool validate_dir_path(const filesystem::path& path) {
        return regex_match(path.string(), dir_pattern);
    }

    const bool validate_file_path(const filesystem::path& path) {
        return regex_match(path.string(), file_pattern);
    }

    const unordered_map<string, regex> RULE = []() {
        unordered_map<string, regex> m;

        m["pwd"]            = regex("^pwd$");
        m["help"]           = regex("^help$");
        m["exit"]           = regex("^exit$");
        m["clear"]          = regex("^clear$");
        m["history"]        = regex("^history$");
        m["date"]           = regex("^date$");
        m["time"]           = regex("^time$");

        const string _glob  = "\\*\\.[A-Za-z]+";

        m["ls"]             = regex("^ls(\\s+-[a-z])?(\\s+(<\\s+)?" + path_dir + ")?(\\s+(>>|>)\\s+" + path_file + ")?$");
        m["cd"]             = regex("^cd(\\s+~|\\s+" + path_dir + ")?$");
        m["mkdir"]          = regex("^mkdir(\\s+" + path_dir + ")+$");
        m["rmdir"]          = regex("^rmdir(\\s+" + path_dir + ")+$");
        m["rm"]             = regex("^rm((\\s+(" + path_file + "|" + _glob + "))+|\\s+-r(\\s+" + path_dir + ")+)$");

        m["touch"]          = regex("^touch\\s+" + path_file + "$");
        m["echo"]           = regex("^echo(\\s+<)?(\\s+\"[^\"]*\")+(\\s+(>|>>)\\s+" + path_file + ")?$");
        m["cp"]             = regex("^cp\\s+(" + path_file + "\\s+(" + path_file + "|" + path_dir + ")|-r\\s+" + path_dir + "\\s+" + path_dir + ")$");
        m["mv"]             = regex("^mv\\s+(" + path_file + "\\s+(" + path_file + "|" + path_dir + ")|" + path_dir + "\\s+" + path_dir + ")$");

        m["cat"]            = regex("^cat\\s+(<\\s+)?" + path_file + "(\\s+(>|>>)\\s+" + path_file + ")?$");
        m["head"]           = regex("^head\\s+((-n|-c)\\s+[0-9]+\\s+)?(<\\s+)?" + path_file + "(\\s+(>|>>)\\s+" + path_file + ")?$");
        m["tail"]           = regex("^tail\\s+((-n|-c)\\s+[0-9]+\\s+)?(<\\s+)?" + path_file + "(\\s+(>|>>)\\s+" + path_file + ")?$");

        m["grep"]           = regex("^grep\\s+((-i|-n|-w|-c|-l|-o)\\s+)*\"[^\"]*\"(\\s+" + path_file + "(\\s+(>|>>)\\s+" + path_file + ")?|(\\s+<\\s+" + path_file + "))$");

        const string _name  = "(-name|-iname)\\s+\"([a-zA-Z_][a-zA-Z_0-9]+|\\*)\\.[A-Za-z]+\"";
        const string _type  = "-type\\s+(f|d)";
        const string _size  = "-size\\s+(\\+|-)?[0-9]+(C|K|M)";

        m["find"]           = regex("^find\\s+" + path_dir + "(\\s+(" + _name + "|" + _type + "|" + _size + "))*(\\s+<\\s+" + path_file + ")?(\\s+(>|>>)\\s+" + path_file + ")?$");

        return m;
    }();

    const unordered_map<string, string> file_path = {
        { "bash",       "Playground/bash.txt" },
        { "essay",      "Playground/essay.txt" },
        { "learning",   "Playground/learning.txt" },
        { "config",     "Playground/Assets/config.ini" },
        { "data",       "Playground/Assets/data.csv" },
        { "AI",         "Playground/Documents/AI.txt" },
        { "template",   "Playground/Documents/template.md" }
    };

    const unordered_map<string, string> file_content = {
        { "bash",       "Bash scripting simplifies repetitive tasks.\nInput parsing is important for custom shells.\nErrors should be handled gracefully in programs.\nA sandbox prevents accidental file deletion.\nFiles can contain logs, notes, or configuration.\nSimple tools often teach important concepts.\nExplore different Linux commands safely.\nAutomation saves time and reduces mistakes.\n" },
        { "essay",      "The quick brown fox jumps over the lazy dog.\nUnderstanding pointers is crucial in C++.\nMemory management prevents leaks and crashes.\nText files can store structured or unstructured data.\nDirectories help organize files logically.\nFunctions modularize your code for reusability.\nDebugging is a critical skill for developers.\nReading documentation saves a lot of time.\nCommand-line tools are powerful and fast.\nAlways test your programs thoroughly.\nLearning never stops in computer science.\n" },
        { "learning",   "Learning C++ is fun and rewarding.\nYou can build small tools like a custom shell.\nFile operations are essential for many programs.\nRedirection allows saving output to files.\nLogical operators control program flow.\nPractice makes perfect in programming.\nVS Code is a versatile editor for C++.\nKeep experimenting with new commands.\nEnjoy building projects step by step.\n" },
        { "config",     "[General]\nAppName=CustomShell\nVersion=1.0\nUser=playground\nHomeDir=E:/Kachra/OS Labs/Custom Shell/Playground\n\n[Settings]\nTheme=Dark\nShowTimestamps=True\n" },
        { "data",       "ID,Name,Role,Department\n1,Talha,Developer,IT\n2,Sara,Tester,QA\n3,Ali,Manager,Operations\n4,Hina,Designer,UI/UX\n5,Omar,Support,Helpdesk\n6,Lara,Analyst,Finance\n7,Usman,Intern,IT\n8,Amna,HR,Human Resources\n9,Zain,DevOps,IT\n10,Mariam,QA Lead,QA\n" },
        { "AI",         "Artificial intelligence is a growing field.\nMachine learning enables computers to learn from data.\nNeural networks mimic the human brain structure.\nData preprocessing improves model accuracy.\nPython is commonly used for AI development.\nExperimentation is key to finding the best solutions.\nStay curious and keep exploring new technologies.\n" },
        { "template",   "# Markdown Document\n\nThis is a simple example of a Markdown file.\n\n## Section 1: Introduction\nMarkdown is a lightweight markup language for creating formatted text using a plain-text editor.\n\n### Key Features\n- Easy to read and write\n- Supports **bold** and *italic* text\n- Can include [links](https://example.com) and images\n\n> Markdown makes documentation simple and elegant.\n" }        
    };

}