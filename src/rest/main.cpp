#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//initializing function

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

enum keyPressSurfaces {
    DEFAULT,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    TOTAL
};

bool init();
bool loadMedia();
void close();

SDL_Window* window = nullptr;
SDL_Surface* screenSurface = nullptr;
SDL_Surface* currentSurface = nullptr;
SDL_Surface* gKeyPressSurface[TOTAL];
SDL_Surface* loadSurface(std::string path);


bool init() {
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "initialization error! " << SDL_GetError() << "\n";
        success = false;
    }
    else {
        window = SDL_CreateWindow("H#Y", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL) {
            std::cout << "Window creation failed! " << SDL_GetError() << "\n";
            success = false;
        }

        else {
            int imgFlags = IMG_INIT_JPG;
            if(!(IMG_Init(imgFlags) & imgFlags)) {
                std::cout << "SDL_Img could not initialize! " << IMG_GetError() << "\n";
                success = false;

            }
            else {
                screenSurface = SDL_GetWindowSurface(window);

            }
        }
    }
    return success;
    

}

bool loadMedia() {
    bool success = true;
    gKeyPressSurface[DEFAULT] = loadSurface("default.jpg");
    if(gKeyPressSurface == NULL) {
        std::cout << "default image loading failed!" << "\n";
        success = false;
    }

    gKeyPressSurface[UP] = loadSurface("up.jpg");
    if(gKeyPressSurface == NULL) {
        std::cout << "up image loading failed!" << "\n";
        success = false;
    }

    gKeyPressSurface[DOWN] = loadSurface("down.jpg");
    if(gKeyPressSurface == NULL) {
        std::cout << "down image loading failed!" << "\n";
        success = false;
    }

    gKeyPressSurface[RIGHT] = loadSurface("right.jpg");
    if(gKeyPressSurface == NULL) {
        std::cout << "right image loading failed!" << "\n";
        success = false;
    }

    gKeyPressSurface[LEFT] = loadSurface("left.jpg");
    if(gKeyPressSurface == NULL) {
        std::cout << "left image loading failed!" << "\n";
        success = false;
    }


    return success;

}

void close() {
    SDL_FreeSurface(currentSurface);
    currentSurface = NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();

}

SDL_Surface* loadSurface(std::string path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    SDL_Surface* optimizedSurface = nullptr;
    if(loadedSurface == NULL) {
        std::cout << "SDL image loading failed! " << path.c_str() << IMG_GetError() << "\n";
    }
    else {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
        if(optimizedSurface == NULL) {
            std::cout << "SDL surface optimization error! " << path.c_str() << SDL_GetError() << "\n";
        }
        SDL_FreeSurface(loadedSurface);

    }
    return optimizedSurface;
}







int main() {

    if(!init()) {
        std::cout << "initializatin failed! " << "\n";
    }
    else{
        if(!loadMedia()) {
            std::cout << "media cannot be loaded! ";
        }
        else {
            currentSurface = gKeyPressSurface[0];
            bool quit = false;
            SDL_Event e;
            while(!quit) {
                while(SDL_PollEvent(&e) != 0) {
                    if(e.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                currentSurface = gKeyPressSurface[UP];
                                break;

                            case SDLK_DOWN:
                                currentSurface = gKeyPressSurface[DOWN];
                                break;

                            case SDLK_RIGHT:
                                currentSurface = gKeyPressSurface[RIGHT];
                                break;

                            case SDLK_LEFT:
                                currentSurface = gKeyPressSurface[LEFT];
                                break;

                            default:
                                currentSurface = gKeyPressSurface[DEFAULT];
                                break;
                        }
                    }
                }
                SDL_Rect strechRect;
                strechRect.x = 0;
                strechRect.y = 0;
                strechRect.w = SCREEN_WIDTH;
                strechRect.h = SCREEN_HEIGHT;

                SDL_BlitScaled(currentSurface, NULL, screenSurface, &strechRect);
                SDL_UpdateWindowSurface(window);
            }
        }

    }
    close();
    return 0;
}
