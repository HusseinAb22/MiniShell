#include "utility.h"

ofstream history_file("history.txt", ios::app);

std::string expand_env_variables(const std::string& input) {
    /*
    Scans the input string for environment variables and replaces them
    with their values. Supports both $VAR and ${VAR} formats.
    For example, "echo $HOME" or "echo ${PATH}" will expand correctly
    to their respective environment variable values.
    */
    std::string result = input;
    std::smatch match;
    std::regex var_pattern(R"(\$\{([^}]+)\}|\$([A-Za-z_][A-Za-z0-9_]*))");

    auto begin = result.cbegin();
    auto end = result.cend();
    std::string expanded;
    while (std::regex_search(begin, end, match, var_pattern)) {
        expanded.append(begin, match[0].first);
        std::string var_name = match[1].matched ? match[1].str() : match[2].str();
        const char* var_value = getenv(var_name.c_str());
        if (var_value) {
            expanded.append(var_value);
        }
        begin = match[0].second;
    }
    expanded.append(begin, end);

    return expanded;
}

void show_history() {
    /*
        Opens and reads the shell command history file line-by-line.
        Each command that was executed in the shell is printed to the terminal.
        This is triggered by the built-in command `myhistory`.
    */
    std::ifstream history_in("history.txt");
    if (!history_in) {
        std::cerr << "Could not open history file." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(history_in, line)) {
        std::cout << line << std::endl;
    }
    history_in.close();
}
