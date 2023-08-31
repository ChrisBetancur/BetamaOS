#include "../drivers/graphics.h"

void main() {
    clear_screen();
    kprint_at("hello", 0, 0);
    kprint("hello there?");
    kprint("hello there?");
}
