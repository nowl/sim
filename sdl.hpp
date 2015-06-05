#ifndef __SDL_HPP__
#define __SDL_HPP__

#include <SDL.h>

#define GL_GLEXT_PROTOTYPES

#ifdef __APPLE__
  #include <gl3.h>
#else
  #include <GL/gl.h>
#endif

#include <string>

#include "color.hpp"

class SDL {
public:
  SDL(const std::string &program_name, unsigned int screen_width, unsigned int screen_height, int cells_width, int cells_height);
	~SDL();

	int getticks();
	void draw();
	bool pollevent(SDL_Event* event);
	void putchar(int x, int y, unsigned char c, const Color& fg, const Color& bg);
	
private:
    int cells_horiz, cells_vert, logical_width, logical_height;
	SDL_Window* window;
	SDL_GLContext context;
    GLuint vao, vbo[5];
    GLuint vertexshader, fragmentshader;
    GLuint shaderprogram;
    GLfloat *centers;
    GLfloat *colorFG;
    GLfloat *colorBG;
    GLubyte *displayChar;
    bool dirty;
    SDL_Event currentSDLEvent;
	std::string program_name;
	unsigned int screen_width, screen_height;

	void setupwindow();
	void setupGL();
};

#endif /* __SDL_HPP__ */
