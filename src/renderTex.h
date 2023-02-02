

class renderTexture {
    public:
        renderTexture();
        ~renderTexture();
        bool init(std::string name, int sw, int sh);
        bool loadFromFile(std::string path);
        int getTexW();
        int getTexH();
        void free();
        void setRect();
        void render(int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flipType);
        void clear();
        void display();
        void close();
    private:
        SDL_Texture* pTexture;
        int texW, texH;
};

