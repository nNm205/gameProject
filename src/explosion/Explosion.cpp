#include "Explosion.h"

Explosion::Explosion(int _x, int _y, SDL_Renderer* renderer)
{
    LoadTexture("./assets/images/effect/explosion.png", renderer);
    SetFrameClip();
    x = _x;
    y = _y;
}

Explosion::~Explosion()
{
    Free();
}

void Explosion::SetFrameClip()
{
    for(int i = 0; i < NUMBER_OF_FRAMES; i++){
        frameClip[i].x = EXPLOSION_WIDTH * i;
        frameClip[i].y = 0;
        frameClip[i].w = EXPLOSION_WIDTH;
        frameClip[i].h = EXPLOSION_HEIGHT;
    }
}

void Explosion::Render(SDL_Renderer* renderer)
{
    if(currentFrame >= NUMBER_OF_FRAMES){
        currentFrame = 0;
        state = CHARACTER_STATE::DEAD;
    }

    SDL_Rect* currentClip = &frameClip[currentFrame];
    SDL_Rect renderQuad = {x, y, EXPLOSION_WIDTH, EXPLOSION_HEIGHT};
    Base::Render(renderer, currentClip, &renderQuad);

    currentFrame++;
}

