#include "Base.h"

Base::Base()
{
    x = 0;
    y = 0;
    texture = nullptr;
}

Base::~Base()
{
    Free();
}

void Base::Free()
{
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

SDL_Surface* Base::LoadSurface(const char* path)
{
    SDL_Surface* loadedSurface = IMG_Load(path);
    if(loadedSurface == nullptr){
        printf("Unable to load image %s! IMG_Load Error: %s\n", path, IMG_GetError());
        return nullptr;
    }
    return loadedSurface;
}

bool Base::LoadTexture(const char* path, SDL_Renderer* renderer){
    Free();

    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = LoadSurface(path);
    if(loadedSurface != nullptr){
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if(newTexture == nullptr){
            printf("Unable to create texture from %s! SDL_CreateTextureFromSurface Error: %s\n", path, SDL_GetError());
            return false;
        }

        rect.w = loadedSurface->w;
        rect.h = loadedSurface->h;
        widthFrame = rect.w;
        heightFrame = rect.h;
        SDL_FreeSurface(loadedSurface);
    }

    texture = newTexture;
    return texture != nullptr;
}

void Base::Render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* _rect)
{
    if(texture == nullptr) return;
    SDL_Rect renderQuad = {x, y, rect.w, rect.h};
    if(_rect != nullptr){
        renderQuad.x = _rect->x;
        renderQuad.y = _rect->y;
        renderQuad.w = _rect->w;
        renderQuad.h = _rect->h;
    }
    SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

void Base::HandleMove()
{
    if(inputType.up)    y -= speed;
    if(inputType.down)  y += speed;
    if(inputType.left)  x -= speed;
    if(inputType.right) x += speed;
}


