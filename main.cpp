#include <stdlib.h>
#include <stdio.h>

#include "sdl.hpp"
#include "djikstra.hpp"

#define MAP_WIDTH 1000
#define MAP_HEIGHT 1000

int constant_cost(int x, int y) {
	if(x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT)
		return 1;
	else
		return -1;
}

int main(int argc, char *argv[])
{
	SDL sdl("test", 1920, 1080);

	int frames = 0;
	SDL_Event event;
	bool running = true;
	uint32_t start_time = sdl.getticks();
	while (running)
	{
		while (sdl.pollevent(&event))
		{
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
				running = false;
		}

		for (int i=0; i<1000; i++) {
			Color fg = {(float)rand()/INT_MAX, (float)rand()/INT_MAX, (float)rand()/INT_MAX};
			//Color bg = {(float)rand()/INT_MAX, (float)rand()/INT_MAX, (float)rand()/INT_MAX};
			Color bg = {0, 0, 0};
			
			sdl.putchar(rand()%CELLS_HORIZ, rand()%CELLS_VERT, rand()%256, fg, bg);
		}
			
		frames++;
			
		sdl.draw();
	}
	uint32_t end_time = sdl.getticks();

	printf("fps: %.2f\n", (float)frames/(end_time-start_time)*1000);
	
	Map map(MAP_WIDTH, MAP_HEIGHT);

	MapInterface interface = {constant_cost};

	std::vector<Point> goals = {{10, 10},
								{5, 5},
								{10, 35},
								{11, 35}};

	calccosts(map, interface, goals);

	return 0;
}

