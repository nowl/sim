#include <stdlib.h>
#include <stdio.h>

#include "rng.hpp"
#include "sdl.hpp"
#include "djikstra.hpp"
#include "message.hpp"

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
    RNG::init();
	SDL sdl("test", 1920, 1080);

	int frames = 0;
	SDL_Event event;
	bool running = true;
	uint32_t start_time = sdl.getticks();

	for (int i=0; i<10000; i++) {
		Color fg = {RNG::f(), RNG::f(), RNG::f()};
		Color bg = {0, 0, 0};
					
		sdl.putchar(RNG::u()%CELLS_HORIZ, RNG::u()%CELLS_VERT,
					RNG::u()%256, fg, bg);
		
		//sdl.putchar(0, 0, '@', fg, bg);
	}
	
	while (running)
	{
		while (sdl.pollevent(&event))
		{
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
				running = false;

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d)
			{
				for (int i=0; i<10000; i++) {
					Color fg = {RNG::f(), RNG::f(), RNG::f()};
					Color bg = {0, 0, 0};
					
					sdl.putchar(RNG::u()%CELLS_HORIZ, RNG::u()%CELLS_VERT,
								RNG::u()%256, fg, bg);

					sdl.putchar(0, 0, '@', fg, bg);
				}
			}
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
	
	Point point_tmp = {4,5};

	Message *message = Message::make(0, 0, 0, point_tmp);

	Point this_point = message->get_payload<Point>();
		printf("%d, %d\n", this_point.x, this_point.y);
	
	return 0;
}

