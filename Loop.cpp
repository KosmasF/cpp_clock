#include "Loop.hpp"

bool Loop() {
	SDL_Event e;

	while( SDL_PollEvent( &e ) != 0 ) {
        if(e.type == SDL_QUIT)
        {
            return false;
        }
    }
    return true;
}