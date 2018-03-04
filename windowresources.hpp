#ifndef WINDOW_H
#define WINDOW_H

#include<SDL2/SDL.h>
#include<system_error>
#include<type_traits>

namespace sdl2 {
    using window_ptr_t = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
    using renderer_ptr_t = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

    template<typename Creator, typename Destructor, typename... Arguments>
    auto make_resource(Creator c, Destructor d, Arguments&&... args)
    {
        auto r = c(std::forward<Arguments>(args)...);
        if (!r) { throw std::system_error(errno, std::generic_category()); }
        return std::unique_ptr<std::decay_t<decltype(*r)>, decltype(d)>(r, d);
    }

    inline window_ptr_t make_window(const char* title, int x, int y, int w, int h, Uint32 flags) {
        return make_resource(SDL_CreateWindow, SDL_DestroyWindow, title, x, y, w, h, flags);
    }
    inline renderer_ptr_t make_renderer(SDL_Window* w, int x, Uint32 flags) {
        return make_resource(SDL_CreateRenderer, SDL_DestroyRenderer, w, x, flags);
    }
}

#endif //WINDOW_H
