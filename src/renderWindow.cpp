#include <iostream> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderWindow.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
  

renderWindow::renderWindow() {
    mTexture = NULL;
    texW = 0;
    texH = 0;
}
renderWindow::~renderWindow() {
    free();
}
  

bool renderWindow::init(std::string name, int sw, int sh) {
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL initialization failed! " << SDL_GetError() << "\n";
        success = false;
    }
    else {
        gWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sw, sh, SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
            std::cout << "unable to create window SDL error! " << SDL_GetError() << "\n";
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL) {
                std::cout << "unable to create rendrerer SDL Error! " << SDL_GetError() << "\n";
                success = false;
                }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image initialization failed " << IMG_GetError() << "\n";
                    success = false;
                }
            }
        }
    }
    return success;
}


bool renderWindow::loadFromFile(std::string path) {
    free();
    SDL_Surface* loadedSurface = NULL;
    SDL_Texture* temmTexture = NULL;
    loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        std::cout << "surface cant get created " << SDL_GetError() << "\n";
    }
    else {
        temmTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(temmTexture == NULL) {
            std::cout << "unable to create texture from surface " << SDL_GetError() << "\n";
        }
        else {
            texW = 640;
            texH = 480;
            SDL_FreeSurface(loadedSurface);
        }
    }
    mTexture = temmTexture;
    return mTexture != NULL;
}

void renderWindow::free() {
    if(mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        texW = 0;
        texH = 0;
    }
}

void renderWindow::render(int x, int y) {
    SDL_Rect dest = {x, y, texW, texH};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &dest);
}

void renderWindow::clear() {
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
}

void renderWindow::display() {
    SDL_RenderPresent(gRenderer);
}

void renderWindow::close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    IMG_Quit();
    SDL_Quit();
}



