#include "Eye.h"
#include "../bullet/Bullet.h"

Eye::Eye(SDL_Renderer* renderer)
{
    type = ENEMY_TYPE::EYE;
    state = CHARACTER_STATE::FLYING;
    hp = 100;
    deviation = 0;

    LoadTextureViaType(renderer);
}

Eye::~Eye()
{
    Free();
}

void Eye::HandleAttackRandomly(SDL_Renderer* renderer)
{
    int currentTime = SDL_GetTicks();
    if(currentTime % 2000 < 15) bullets.push_back(new Bullet(BULLET_TYPE::ENEMY_BULLET, x + widthFrame, y + 10, renderer));
}


