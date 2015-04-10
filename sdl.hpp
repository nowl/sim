#ifndef __SDL_HPP__
#define __SDL_HPP__

#include <SDL.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

#include <string>

#include "color.hpp"

// this is the number of cells across and down the screen
//#define CELLS_HORIZ    120
//#define CELLS_VERT     38

//#define CELLS_HORIZ    120
#define CELLS_HORIZ    200
#define CELLS_VERT     (38 * CELLS_HORIZ / 120)

// this is the logical size of the screen
#define WIDTH   (CELLS_HORIZ*9)
#define HEIGHT  (CELLS_VERT*16)

#define FALSE 0
#define TRUE  1

// this is the actual size of the screen in pixels
//#define SCREENWIDTH   1920
//#define SCREENHEIGHT  (SCREENWIDTH * 9 / 16)

class SDL {
public:
	SDL(const std::string &program_name, unsigned int screen_width, unsigned int screen_height);
	~SDL();

	int getticks();
	void draw();
	bool pollevent(SDL_Event* event);
	void putchar(int x, int y, unsigned char c, const Color& fg, const Color& bg);
	
private:
	SDL_Window* window;
	SDL_GLContext context;
    GLuint vao, vbo[5];
    GLuint vertexshader, fragmentshader;
    GLuint shaderprogram;
    GLfloat centers[6*2*CELLS_HORIZ*CELLS_VERT];
    GLfloat colorFG[3*CELLS_HORIZ*CELLS_VERT];
    GLfloat colorBG[3*CELLS_HORIZ*CELLS_VERT];
    GLubyte displayChar[CELLS_HORIZ*CELLS_VERT];
    bool dirty;
    SDL_Event currentSDLEvent;
	std::string program_name;
	unsigned int screen_width, screen_height;

	void setupwindow();
	void setupGL();
};

#endif /* __SDL_HPP__ */
