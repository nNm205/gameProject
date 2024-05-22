#include "../common/Common.h"
#include "Horn.h"
#include "../bullet/Bullet.h"

Horn::Horn(SDL_Renderer* renderer)
{
    type = ENEMY_TYPE::HORN;
    state = CHARACTER_STATE::FLYING;
    hp = 100;
    deviation = 0;

    LoadTextureViaType(renderer);
}

Horn::~Horn()
{
    Free();
}

void Horn::HandleAttackRandomly(SDL_Renderer* renderer)
{
    int currentTime = SDL_GetTicks();
    if(currentTime % 2000 < 15) bullets.push_back(new Bullet(BULLET_TYPE::ENEMY_BULLET, x + widthFrame, y + 10, renderer));
}
