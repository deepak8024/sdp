#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderWindow.h"
#include "game.h"

game games;

renderWindow window;



bool loadMedia();

bool loadMedia() {
    bool success = true;
    if(!window.loadFromFile("foo.png")) {
        std::cout << "unable loade media " << SDL_GetError() << "\n";
        success = false;
    }
    return success;
}


int main(){
    if(!window.init("HELLO", 640, 480)){
        std::cout << "initialization failed " << "\n";
    }
    else {
        if(!loadMedia()) {
            std::cout << "unable to load media " << "\n";
        }
        else {
            bool quit = false;
            SDL_Event ev;
            while(!quit) {
                while(SDL_PollEvent(&ev) != 0) {
                    if(ev.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                window.clear();

                window.render(0, 0);

                window.display();
            }
        }
    }
    window.close();
    return 0;
}

