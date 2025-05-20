#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

std::string expand_env_variables(const std::string& input);
void show_history();