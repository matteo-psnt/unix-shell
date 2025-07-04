#pragma once
#include <fcntl.h>
#include <string>
#include <unistd.h>
#include <vector>

std::string trim_whitespace(const std::string& str);
std::string find_executable(const std::string& cmd_name);
void run_external_command(const std::vector<std::string>& tokens);
bool execute_command(const std::vector<std::string>& tokens);
std::vector<std::string> tokenize_input(const std::string& input);

// New functions for advanced parsing
struct CommandSequence {
    std::vector<std::string> tokens;
    std::string operator_type;  // "", ";", "&&", "||"
};

std::vector<CommandSequence> parse_command_sequence(const std::string& input);
bool execute_command_sequence(const std::vector<CommandSequence>& sequence);