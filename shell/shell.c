
#include "shell.h"
#include "../libc/string.h"
#include "../drivers/graphics.h"
#include "../libc/types.h"

int cmd_index = 0;

// cmd temporarly defined in shell, will move to seperate file
static void echo(void* data);

cmd_entry_t* get_cmd_entry(char cmd_str[]);

char** split_buffer(char buffer[]);

/*
 * Public Functions
 */
void register_cmd(cmd_t cmd) {
    cmd_entries[cmd_index].name = "ECHO";
    cmd_entries[cmd_index].handler = cmd;
    cmd_index++;
    kprint("registering cmd...\n");
    kprint(cmd_entries[cmd_index].name);
    kprint("\n");
}

void handle_cmd(char buffer[]) {
    // WORK ON SPLITTING STRING
    char** tokens = split_str(buffer, ' ', 2);

    // returns not right, not showing echo
    kprint(tokens[0]);
    cmd_entry_t *entry = get_cmd_entry(tokens[0]);

    if (entry == NULL){
        kprint("error entry not found");
        return;
    }

    kprint("handler: ");
    kprint(entry->name);
    kprint("\n");
    cmd_t handler = entry->handler;

    kprint("handler accessing...\n\n");
    handler(tokens[1]);
}

// install all the commands for the shell here
void shell_install() {
    register_cmd(echo);
}

/*
 * Private Functions
 */
cmd_entry_t* get_cmd_entry(char cmd_str[]) {
    for (int i = 0; i < CMD_ENTRIES; i++) {
        kprint("current ");
        kprint(cmd_entries[i].name);
        kprint(", ");
        kprint(cmd_str);
        kprint("\n");
        if (strcmp(cmd_entries[i].name, cmd_str) == 0) {
            kprint("found-> ");
            kprint(cmd_str);
            kprint("\n");
            return &cmd_entries[i];
        }
    }
    return NULL;
}

// MAY REPLACE THIS WITH A LEXER TO BETTER READ TERMINAL INPUT
// CREATE A TUPLE STRUCTURE

static void echo(void* data) {
    kprint((char*) data);
}

