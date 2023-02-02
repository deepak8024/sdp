#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



class renderWindow {
    public:
        renderWindow();
        ~renderWindow();
        bool init(std::string windowName, int sw, int sh);
        bool loadFromFile(std::string path);
        void free();
        void render(int x, int y);
        void clear();
        void display();
        void close();
        
    private:
        SDL_Texture* mTexture;
        int texW;
        int texH;

};

