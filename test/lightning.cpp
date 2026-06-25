#include <iostream>
#include <string>

#include "../engine/command_handler.h"
#include "../engine/command_parser.h"

int main() {
    CommandHandler handler;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line == "QUIT" || line == "quit") {
            break;
        }

        Command command;
        if (!parse_command(line, command)) {
            if (!line.empty()) {
                std::cout << "ERR bad command\n";
            }
            continue;
        }

        Response response = handler.execute(command);
        std::cout << response.text << '\n';
    }

    return 0;
}
