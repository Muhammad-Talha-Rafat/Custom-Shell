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

    const string path_dir = R"((?:\.?\.?/|/)?(?:[A-Za-z_][A-Za-z0-9_]*|\.\.?)(?:/(?:[A-Za-z_][A-Za-z0-9_]*|\.\.?))*/?)";
    const string path_file = R"((?:\.?\.?/|/)?(?:[A-Za-z_][A-Za-z0-9_]*|\.\.?)(?:/(?:[A-Za-z_][A-Za-z0-9_]*|\.\.?))*/?[A-Za-z_][A-Za-z0-9_]*\.[A-Za-z]+)";

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
}