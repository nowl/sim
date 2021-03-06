#include "sdl.hpp"

#include "data.h"
#include "codepage-437-hex.h"

static void sdldie(const char *msg)
{
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}

void SDL::setupwindow()
{
	// init sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        sdldie("Unable to initialize SDL");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow(program_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  screen_width, screen_height,
							  SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window)
        sdldie("Unable to create window");

    context = SDL_GL_CreateContext(window);

	if (!context)
		sdldie("");

    SDL_GL_SetSwapInterval(1);
}

void SDL::setupGL()
{
    int IsCompiled_VS, IsCompiled_FS;
    int IsLinked;
    int maxLength;
    char *vertexInfoLog;
    char *fragmentInfoLog;
    char *shaderProgramInfoLog;

    GLuint texture;

    GLint major_version, minor_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    glGetIntegerv(GL_MINOR_VERSION, &minor_version);
    printf("major GL version: %d\n", major_version);
    printf("minor GL version: %d\n", minor_version);
    if (!(major_version > 3 || (major_version == 3 && minor_version >= 3))) {
        printf("minimum GL version required 3.3\n");
        exit(-1);
    }
	
    glActiveTexture(GL_TEXTURE0);
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned char alpha_vals[TEXTURE_WIDTH * TEXTURE_HEIGHT];
    for(int i=0; i<codepage437_image.width * codepage437_image.height / 8; i++) {
        unsigned char v = codepage437_image.pixel_data[i];
        
        alpha_vals[i*8] = ((v >> 7) & 1) * 0xff;
        alpha_vals[i*8+1] = ((v >> 6) & 1) * 0xff;
        alpha_vals[i*8+2] = ((v >> 5) & 1) * 0xff;
        alpha_vals[i*8+3] = ((v >> 4) & 1) * 0xff;
        alpha_vals[i*8+4] = ((v >> 3) & 1) * 0xff;
        alpha_vals[i*8+5] = ((v >> 2) & 1) * 0xff;
        alpha_vals[i*8+6] = ((v >> 1) & 1) * 0xff;
        alpha_vals[i*8+7] = (v & 1) * 0xff;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, codepage437_image.width,
                 codepage437_image.height, 0, GL_RED, GL_UNSIGNED_BYTE,
                 alpha_vals);

    for (int y=0; y<cells_vert; y++)
    {
        for (int x=0; x<cells_horiz; x++)
        {
			centers[y*cells_horiz*2 + x*2] = x*9 + 4.5;
			centers[y*cells_horiz*2 + x*2+1] = y*16 + 8;
        }
    }

    for(int i=0; i<3*cells_horiz*cells_vert; i++) {
        colorFG[i] = 1;
        colorBG[i] = 0;
    }

    for(int i=0; i<cells_horiz*cells_vert; i++) {
        displayChar[i] = 0;
    }

	float block[] = {
		9, 0,
		0, 0,
		0, 16,
		0, 16,
		9, 16,
		9, 0
	};

    glGenVertexArrays(1, &(vao));
    glBindVertexArray(vao);
    glGenBuffers(5, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, 2*cells_horiz*cells_vert * sizeof(GLfloat), centers, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribDivisor(0, 1);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, 3*cells_horiz*cells_vert * sizeof(GLfloat), colorFG, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, 3*cells_horiz*cells_vert * sizeof(GLfloat), colorBG, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribDivisor(2, 1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ARRAY_BUFFER, cells_horiz*cells_vert, displayChar, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(3, 1, GL_UNSIGNED_BYTE, GL_FALSE, 0, 0);
	glVertexAttribDivisor(3, 1);
    glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
    glBufferData(GL_ARRAY_BUFFER, 6*2 * sizeof(GLfloat), block, GL_STATIC_DRAW);
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribDivisor(4, 0);
    glEnableVertexAttribArray(4);

    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *vertexsourcePtr = vertex_shader_src;
    glShaderSource(vertexshader, 1, (const GLchar**)&vertexsourcePtr, 0);
    glCompileShader(vertexshader);
    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &IsCompiled_VS);
    if(IsCompiled_VS == 0)
    {
       glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &maxLength);
       vertexInfoLog = (char *)malloc(maxLength);
       glGetShaderInfoLog(vertexshader, maxLength, &maxLength, vertexInfoLog);
       printf("vertex shader error: %s\n", vertexInfoLog);
	   printf("%s\n", SDL_GetError());
       free(vertexInfoLog);
       return;
    }

    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *fragmentsourcePtr = fragment_shader_src;
    glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsourcePtr, 0);
    glCompileShader(fragmentshader);
    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &IsCompiled_FS);
    if(IsCompiled_FS == 0)
    {
       glGetShaderiv(fragmentshader, GL_INFO_LOG_LENGTH, &maxLength);
       fragmentInfoLog = (char *)malloc(maxLength);
       glGetShaderInfoLog(fragmentshader, maxLength, &maxLength, fragmentInfoLog);
       printf("fragment shader error: %s\n", fragmentInfoLog);

       free(fragmentInfoLog);
       return;
    }

    shaderprogram = glCreateProgram();
    glAttachShader(shaderprogram, vertexshader);
    glAttachShader(shaderprogram, fragmentshader);
    glLinkProgram(shaderprogram);

    glGetProgramiv(shaderprogram, GL_LINK_STATUS, (int *)&IsLinked);
    if(IsLinked == 0)
    {
       glGetProgramiv(shaderprogram, GL_INFO_LOG_LENGTH, &maxLength);
       shaderProgramInfoLog = (char *)malloc(maxLength);
       glGetProgramInfoLog(shaderprogram, maxLength, &maxLength, shaderProgramInfoLog);

       free(shaderProgramInfoLog);
       return;
    }

    glUseProgram(shaderprogram);

    GLint mvp = glGetUniformLocation(shaderprogram, "MVP" );

    float r = logical_width;
    float l = 0;
    float t = logical_height;
    float b = 0;
    float f = -1;
    float n = 1;
    float mvp_ptr[] = {2/(r-l), 0, 0, 0,
                       0, 2/(t-b), 0, 0,
                       0, 0, -2/(f-n), 0,
                       -(r+l)/(r-l), -(t+b)/(t-b), -(f+n)/(f-n), 1};

    glUniformMatrix4fv(mvp, 1, GL_FALSE, mvp_ptr);

    glActiveTexture(GL_TEXTURE0);
    GLint texture_location = glGetUniformLocation(shaderprogram, "in_Texture");
    glUniform1i(texture_location, 0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendEquation( GL_FUNC_ADD );
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void SDL::draw() {
	dirty = true;
    if(dirty) {
        dirty = false;

		glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferSubData(GL_ARRAY_BUFFER,
                        0,
                        3*cells_horiz*cells_vert*sizeof(GLfloat),
                        colorFG);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
        glBufferSubData(GL_ARRAY_BUFFER,
                        0,
                        3*cells_horiz*cells_vert*sizeof(GLfloat),
                        colorBG);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
        glBufferSubData(GL_ARRAY_BUFFER,
                        0,
                        cells_horiz*cells_vert,
                        displayChar);

        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, cells_horiz*cells_vert);
        SDL_GL_SwapWindow(window);
    }
}

SDL::SDL(const std::string &program_name, unsigned int screen_width, unsigned int screen_height, int cells_width, int cells_height)
	: program_name(program_name),
	  screen_width(screen_width),
	  screen_height(screen_height)
{
    cells_horiz = cells_width;
    cells_vert = cells_height;
    logical_width = cells_horiz * 9;
    logical_height = cells_vert * 16;

    centers = new GLfloat [6*2*cells_horiz*cells_vert];
    colorFG = new GLfloat [3*cells_horiz*cells_vert];
    colorBG = new GLfloat [3*cells_horiz*cells_vert];
    displayChar = new GLubyte [cells_horiz*cells_vert];

    dirty = true;

    setupwindow();
    setupGL();
}

SDL::~SDL() {
    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
    glDetachShader(shaderprogram, vertexshader);
    glDetachShader(shaderprogram, fragmentshader);
    glDeleteProgram(shaderprogram);
    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);
    glDeleteBuffers(5, vbo);
    glDeleteVertexArrays(1, &vao);

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void SDL::putchar(int x, int y, unsigned char c, const Color& fg, const Color& bg)
{
    //int index = (cells_vert-y-1) + x * cells_vert;
	int index = (cells_vert-y-1) * cells_horiz + x;
	displayChar[index] = c;
	colorFG[index*3] = fg.r;
	colorFG[index*3+1] = fg.g;
	colorFG[index*3+2] = fg.b;
	colorBG[index*3] = bg.r;
	colorBG[index*3+1] = bg.g;
	colorBG[index*3+2] = bg.b;
    
    dirty = true;
}

bool SDL::pollevent(SDL_Event *event) {
    int result = SDL_PollEvent(&currentSDLEvent);
	if (result) {
		*event = currentSDLEvent;
		
		return true;
	}

	return false;
}

int SDL::getticks() {
    return SDL_GetTicks();
}
