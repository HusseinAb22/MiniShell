#include "run_shell.h"

void help() {
    /*
        Prints a helpful message listing all supported built-in and external
        commands available in the shell. This is shown when the user types 'help'.
    */
    cout << "This is my shell implementation. Available commands:\n";
    cout << "cd <dir>       - Change directory\n";
    cout << "myjobs         - List background jobs\n";
    cout << "myhistory      - Show command history\n";
    cout << "exit           - Exit the shell\n";
    cout << "help           - Show this help message\n";
    cout << "sleep <sec>    - Pause execution for <sec> seconds (external)\n";
    cout << "who            - Show who is logged in (external)\n";
}
void run() {
    /*
        This is the main loop of the shell. It displays a prompt, reads user input,
        processes and executes commands, handles background execution, and
        supports built-in commands like cd, myjobs, myhistory, and help.
    */
    string command_line;
    bool running = true;

    cout << "<Welcome in my minishell>\n";

    while (running) {
        cout << "<shell>";
        getline(cin, command_line);

        if (command_line == "exit") {
            running = false;
            continue;
        }

        check_background_jobs();

        command_line = expand_env_variables(command_line);
        history_file << command_line << endl;

        vector<string> args = parse_command(command_line);
        if (args.empty()) continue;

        bool run_in_background = args.back() == "&";
        if (run_in_background) args.pop_back();

        if (args[0] == "cd") {
            handle_cd(args);
            continue;
        }

        if (args[0] == "myjobs") {
            list_background_jobs();
            continue;
        }

        if (args[0] == "myhistory") {
            show_history();
            continue;
        }
        if (args[0] == "help") {
            help();
            continue;
        }


        execute_command(args, command_line, run_in_background);
    }

    history_file.close();
}

