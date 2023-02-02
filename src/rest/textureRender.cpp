#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include "textureRender.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Rect clip[4];

textureRender::textureRender() {
    //initialize
    mTexture = NULL;
    

    mWidth = 0;
    mHeight = 0;

}
textureRender::~textureRender() {
    //Deallocate
    free();
}



bool textureRender::init(int sw, int sh) {
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL initilization failed SDL Error! " << SDL_GetError() << "\n";
        success = false;
    }
    else {
        gWindow = SDL_CreateWindow("HUSH", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sw, sh, SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
            std::cout << "unable to create gWindow SDL Error! " << SDL_GetError() << "\n";
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL) {
                std::cout << "unable to create renderer SDL Error! " << SDL_GetError() << "\n";
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "unable to initialize PNG image " << IMG_GetError() << "\n";
                    success = false;
                }
            }
        }

    }
    return success;

}



bool textureRender::loadFromFile(std::string path) {

    // dellocate texture surface 
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = NULL;
    loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        std::cout << "unable to load image! " << path.c_str() << IMG_GetError() << "\n";
    }
    else {

        //SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        

        //Creating textrue from surface
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL) {
            std::cout << "unable to create texture from " << path.c_str() << "SDL Error! " << SDL_GetError() << "\n";
        }
        else {
            //Get image dimension
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;

        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;

}





void textureRender::free() {
    if(mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
void textureRender::setRect() {
    //Set top left sprite


    clip[ 0 ] = {0, 0, 64, 205};
    clip[ 1 ] = {64, 0, 64, 205};
    clip[ 2 ] = {128, 0, 64, 205};
    clip[ 3 ] = {192, 0, 64, 205};

}

void textureRender::render(int x, int y, int i) {
    SDL_Rect renderRect = {0, 0, 2*5*64, 480};
    SDL_RenderCopy(gRenderer, mTexture, &clip[i], &renderRect);
}


int textureRender::getWidth() {
    return mWidth;
}

int textureRender::getHeight() {
    return mHeight;
}

void textureRender::clear() {
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
}

void textureRender::display() {
    SDL_RenderPresent(gRenderer);
}

void textureRender::close() {
    
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}


