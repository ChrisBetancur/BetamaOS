
#include "shell.h"
#include "../libc/string.h"
#include "../drivers/graphics.h"
#include "../libc/types.h"

int cmd_index = 0;

// cmd temporarly defined in shell, will move to seperate file
static void echo(void* data);

cmd_entry_t* get_cmd_entry(char cmd_str[]);

char** split_buffer(char buffer[]);

// HANDLE COMMANDS LIKE HOW INTERRUPTS ARE HANDLEED IN ISR.C
void handle_cmd(char buffer[]);

/*
 * Public Functions
 */
void register_cmd(cmd_t cmd) {
    cmd_entries[cmd_index].name = "ECHO";
    cmd_entries[cmd_index].handler = cmd;
    cmd_index++;
}


// install all the commands for the shell here
void shell_install() {
    register_cmd(echo);
}

void user_input(char *input) {
    handle_cmd(input);
    kprint("betama$ ");
}

/*
 * Private Functions
 */
cmd_entry_t* get_cmd_entry(char cmd_str[]) {
    for (int i = 0; i < CMD_ENTRIES; i++) {
        if (strcmp(cmd_entries[i].name, cmd_str) == 0) {
            return &cmd_entries[i];
        }
    }
    return NULL;
}

// cmd should only be tokens[0] which is one word
void handle_cmd(char buffer[]) {
    // WORK ON SPLITTING STRING
    char** tokens = single_split_str(buffer, ' ');

    // returns not right, not showing echo

    cmd_entry_t *entry = get_cmd_entry(tokens[0]);

    if (entry == NULL){
        kprint("Command not found\n");
        return;
    }

    /*kprint("handler: ");
    kprint(entry->name);
    kprint("\n");*/
    cmd_t handler = entry->handler;

    //kprint("handler accessing...\n\n");
    handler(tokens[1]);
}

// MAY REPLACE THIS WITH A LEXER TO BETTER READ TERMINAL INPUT
// CREATE A TUPLE STRUCTURE

static void echo(void* data) {
    kprint((char*) data);
    kprint("\n");
}
