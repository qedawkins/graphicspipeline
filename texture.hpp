#ifndef TEXTURE_H
#define TEXTURE_H

#include<iostream>
#include<stdexcept>
#include<string>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>

class texture {
    public:
    texture() : sprite(nullptr), w(0), h(0) {};
    ~texture();
    void loadTexture(std::string path, SDL_Renderer* rend);
    void render(int x, int y, SDL_Renderer* rend);
    SDL_Texture* sprite;
    int w;
    int h;
    private:
};

#endif //TEXTURE_H
