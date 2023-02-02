#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "textureRender.h"


bool loadMedia();
textureRender window;
const int animFrame = 4;

bool loadMedia() {
    bool success = true;
    if(!window.loadFromFile("foo.png")) {
        std::cout << "unable to load fadein.png: " << SDL_GetError() << "\n";
        success = false;
    }
    return success;
}

int main() {

    if(!window.init(640, 480)) {
        std::cout << "initilization error! " << "\n";
    }
    else {
        if(!loadMedia()) {
            std::cout << "media could not get loaded! " << "\n";
        }
        else {
            
            window.setRect();
            bool quit = false;
            SDL_Event e;
            int frame = 0;
            while(!quit) {
                while(SDL_PollEvent(&e) != 0) {
                    if(e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                window.clear();
                window.render(288, 138, (frame/4));
                
                window.display();
                frame+=1;

                if(frame/4 >= 4) {
                    frame = 0;
                }
            }
        }
    }

    window.close();

    return 0;
}
