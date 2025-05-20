#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <map>

using namespace std;

extern ofstream history_file;

vector<string> parse_command(const string& input);
string search_in_path(const string& command);
void execute_command(const vector<string>& args, const string& original_cmd, bool run_in_background);
void execute_pipeline(const vector<vector<string>>& commands);
void handle_cd(const vector<string>& args);
void list_background_jobs();
void check_background_jobs();


