#include "texture.hpp"

texture::~texture() {
    if(sprite != nullptr)
        SDL_DestroyTexture(sprite);
}

void texture::loadTexture(std::string path, SDL_Renderer* rend) {
    SDL_Surface* surf = nullptr;
    surf = IMG_Load(path.c_str());
    if(surf == nullptr) {
        std::cout << IMG_GetError() << std::endl;
        throw std::runtime_error("Unable to load sprite");
    }
    SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0, 0xff, 0xff));
    sprite = SDL_CreateTextureFromSurface(rend, surf);
    if(sprite == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        throw std::runtime_error("Unable to create texture");
    }
    w = surf->w;
    h = surf->h;
    SDL_FreeSurface(surf);
}

void texture::render(int x, int y, SDL_Renderer* rend) {
    SDL_Rect rendrect = {x, y, w, h};
    SDL_RenderCopy(rend, sprite, NULL, &rendrect);
}
