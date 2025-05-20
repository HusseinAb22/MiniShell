// Updated shell.cpp
#include "shell.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <regex>
#include <cstring>

map<pid_t, string> background_jobs;

vector<string> parse_command(const string& input) {
    istringstream iss(input);
    vector<string> args;
    string token;
    while (iss >> token) {
        args.push_back(token);
    }
    return args;
}

string search_in_path(const string& command) {
    char* path_env = getenv("PATH");
    if (!path_env) return "";

    istringstream iss(path_env);
    string dir;
    while (getline(iss, dir, ':')) {
        string full_path = dir + "/" + command;
        if (access(full_path.c_str(), X_OK) == 0) {
            return full_path;
        }
    }
    return "";
}

void execute_pipeline(const vector<vector<string>>& commands) {
    int num_cmds = commands.size();
    int in_fd = 0;
    int pipe_fd[2];

    for (int i = 0; i < num_cmds; ++i) {
        if (i < num_cmds - 1) pipe(pipe_fd);

        pid_t pid = fork();
        if (pid == 0) {
            if (i > 0) {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (i < num_cmds - 1) {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }

            const vector<string>& cmd = commands[i];
            vector<char*> c_args;
            int fd_in = -1, fd_out = -1;
            for (size_t j = 0; j < cmd.size(); ++j) {
                if (cmd[j] == "<" && j + 1 < cmd.size()) {
                    fd_in = open(cmd[j + 1].c_str(), O_RDONLY);
                    dup2(fd_in, STDIN_FILENO);
                    j++;
                } else if (cmd[j] == ">" && j + 1 < cmd.size()) {
                    fd_out = open(cmd[j + 1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd_out, STDOUT_FILENO);
                    j++;
                } else {
                    c_args.push_back(const_cast<char*>(cmd[j].c_str()));
                }
            }
            c_args.push_back(nullptr);

            string exec_path = search_in_path(c_args[0]);
            execv(exec_path.c_str(), c_args.data());
            perror("execv failed");
            exit(EXIT_FAILURE);
        } else {
            if (i > 0) close(in_fd);
            if (i < num_cmds - 1) {
                close(pipe_fd[1]);
                in_fd = pipe_fd[0];
            }
            waitpid(pid, nullptr, 0);
        }
    }
}

void execute_command(const vector<string>& args, const string& original_cmd, bool run_in_background) {
    vector<vector<string>> pipeline;
    vector<string> current;
    for (const string& arg : args) {
        if (arg == "|") {
            pipeline.push_back(current);
            current.clear();
        } else {
            current.push_back(arg);
        }
    }
    pipeline.push_back(current);

    if (pipeline.size() > 1) {
        execute_pipeline(pipeline);
        return;
    }

    // fallback to regular non-pipe command
    execute_pipeline({args});
}

void list_background_jobs() {
    for (const auto& job : background_jobs) {
        cout << "[PID: " << job.first << "] " << job.second << endl;
    }
}

void check_background_jobs() {
    for (auto it = background_jobs.begin(); it != background_jobs.end(); ) {
        int status;
        pid_t result = waitpid(it->first, &status, WNOHANG);
        if (result > 0) {
            cout << "[PID: " << it->first << "] finished." << endl;
            it = background_jobs.erase(it);
        } else {
            ++it;
        }
    }
}

void handle_cd(const vector<string>& args) {
    const char* target = args.size() > 1 ? args[1].c_str() : getenv("HOME");
    if (chdir(target) != 0) {
        perror(("cd: " + string(target)).c_str());
    }
}