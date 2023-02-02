#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "renderTexture.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Rect srcRect[4];

renderTexture::renderTexture() {
    pTexture = NULL;
    texW = 0;
    texH = 0;
}

renderTexture::~renderTexture() {
    free();
}

bool renderTexture::init(std::string name, int sw, int sh) {
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL initialization failed, SDL error! " << SDL_GetError() << "\n";
        success = false;
    }
    else {
        gWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sw, sh, SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
            std::cout << "Window creation failed! " << SDL_GetError() << "\n";
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL) {
                std::cout << "Renderer creation failed! " << SDL_GetError() << "\n";
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image intialization failed! " << IMG_GetError() << "\n";
                    success = false;
                }
                std::cout << (IMG_Init(imgFlags)&imgFlags) << "\n";
            }
        }
    }
    return success;
}

bool renderTexture::loadFromFile(std::string path) {
    free();
    SDL_Surface* loadedSurface = NULL;
    SDL_Texture* tempTexture = NULL;
    loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        std::cout << "unable to load image! " << IMG_GetError() << "\n";
    }
    else {
        tempTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(tempTexture == NULL) {
            std::cout << "unable to create texture from surface! " << SDL_GetError() << "\n";
        }
        else {
            texW = loadedSurface->w;
            texH = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    pTexture = tempTexture;
    return pTexture != NULL;
}

void renderTexture::free() {
    if(pTexture != NULL) {
        SDL_DestroyTexture(pTexture);
        pTexture = NULL;
        texW = 0;
        texH = 0;
    }
}

int renderTexture::getTexW() {
    return texW;
}

int renderTexture::getTexH() {
    return texH;
}

void renderTexture::setRect() {
    srcRect[0] = {0, 0, texW/4, texH};
    srcRect[1] = {texW/4, 0, texW/4, texH};
    srcRect[2] = {texW/2, 0, texW/4, texH};
    srcRect[3] = {3*texW/4, 0, texW/4, texH};
}

void renderTexture::render(int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flipType) {
    setRect();
    SDL_Rect destRect = {x, y, texW, texH};
    SDL_RenderCopyEx(gRenderer, pTexture, NULL, &destRect, angle, center, flipType);
}

void renderTexture::clear() {
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
}

void renderTexture::display() {
    SDL_RenderPresent(gRenderer);
}

void renderTexture::close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();

}

