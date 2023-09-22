
#ifndef SHELL_H
#define SHELL_H

#include "../libc/types.h"

// all commands must pass data param
typedef void (*cmd_t) (void* data);

typedef struct {
    char* name;
    cmd_t handler;
} cmd_entry_t;

// CURRENTLY COMMANDS SHOULD ONLY BE ONE WORD AND/OR ONE INPUT BESIDE
#define CMD_ENTRIES 1

cmd_entry_t cmd_entries[CMD_ENTRIES];

void register_cmd(cmd_t cmd);

void shell_install();

void user_input(char *input);

#endif
