#include <stdlib.h>
#include <stdio.h>

#include "rng.h"
#include "sdl.h"

int main(int argc, char *argv[])
{
    RNG_init(0x12345678);
	sdl_init("test", 1920, 1080);

	int frames = 0;
	SDL_Event event;
	int running = TRUE;
	uint32_t start_time = sdl_getticks();

	for (int i=0; i<10000; i++) {
		float fg_r = RNG_f();
		float fg_g = RNG_f();
		float fg_b = RNG_f();
					
		sdl_putchar(RNG_u()%CELLS_HORIZ, RNG_u()%CELLS_VERT,
					RNG_u()%256, fg_r, fg_g, fg_b, 0, 0, 0);
		
		//sdl_putchar(0, 0, '@', fg, bg);
	}
	
	while (running)
	{
		int sym;
		uint16_t mod;
		while (sdl_pollevent(&sym, &mod))
		{
			if (sym == SDLK_ESCAPE)
				running = FALSE;

			if (sym == SDLK_d)
			{
				for (int i=0; i<10000; i++) {
					float fg_r = RNG_f();
					float fg_g = RNG_f();
					float fg_b = RNG_f();
					
					sdl_putchar(RNG_u()%CELLS_HORIZ, RNG_u()%CELLS_VERT,
								RNG_u()%256, fg_r, fg_g, fg_b, 0, 0, 0);

					sdl_putchar(0, 0, '@', fg_r, fg_g, fg_b, 0, 0, 0);
				}
			}
		}

		frames++;
        
			
		sdl_draw();
	}
	uint32_t end_time = sdl_getticks();

	printf("fps: %.2f\n", (float)frames/(end_time-start_time)*1000);
	
	return 0;
}

