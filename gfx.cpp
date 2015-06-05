#include "globals.hpp"
#include "gfx.hpp"

void
draw_string_at_pos(const std::string& message, int x, int y, Color c)
{
    for (int i=0; i<message.size(); i++) {
        sdl->putchar(x+i, y, message[i], c, Color(0,0,0));
    }
}
