#pragma once

#include <string>

#include "command.h"

bool parse_command(const std::string& line, Command& command);
