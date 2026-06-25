#pragma once

#include "command.h"
#include "../manager/ledger.h"

class CommandHandler {
public:
    Response execute(const Command& command);

private:
    Ledger ledger_;
};
