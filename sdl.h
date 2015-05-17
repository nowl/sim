#ifndef __SDL_H__
#define __SDL_H__

#include <SDL.h>

#define GL_GLEXT_PROTOTYPES

#ifdef __APPLE__
  #include <gl3.h>
#else
  #include <GL/gl.h>
#endif

// this is the number of cells across and down the screen
//#define CELLS_HORIZ    120
//#define CELLS_VERT     38

#define CELLS_HORIZ    120
//#define CELLS_HORIZ    200
#define CELLS_VERT     (38 * CELLS_HORIZ / 120)

// this is the logical size of the screen
#define WIDTH   (CELLS_HORIZ*9)
#define HEIGHT  (CELLS_VERT*16)

#define FALSE 0
#define TRUE  1

void sdl_init(const char *program_name, unsigned int screen_width, unsigned int screen_height);
void sdl_destroy();

int  sdl_getticks();
void sdl_draw();
int  sdl_pollevent(SDL_Event* event);
void sdl_putchar(int x, int y, unsigned char c,
				 float fg_r, float fg_g, float fg_b,
				 float bg_r, float bg_g, float bg_b);
	
#endif /* __SDL_H__ */
