#include "Bullet.h"

Bullet::Bullet()
{
    widthFrame = 0;
    heightFrame = 0;
}

Bullet::Bullet(BULLET_TYPE _bulletType, int _x, int _y, SDL_Renderer* renderer)
{
    loadBulletViaType(_bulletType, renderer);
    x = _x;
    y = _y + 10;
}

Bullet::~Bullet()
{
    Free();
}

void Bullet::loadBulletViaType(BULLET_TYPE _bulletType, SDL_Renderer* renderer)
{
    bulletType = _bulletType;
    switch(bulletType){
        case BULLET_TYPE::PLAYER_BULLET:
            LoadTexture("./assets/images/bullets/pro.png", renderer);
            rect = {0, 0, 27, 9};
            speed = 14;
            damage = 20;
            break;
        case BULLET_TYPE::ENEMY_BULLET:
            LoadTexture("./assets/images/bullets/mid.png", renderer);
            rect = {0, 0, 25, 25};
            speed = -15;
            damage = 10;
            break;
        default:
            break;
    }
}

void Bullet::Render(SDL_Renderer* renderer, SDL_Rect* _clip, SDL_Rect* _rect)
{
    x += speed;
    if(_rect == nullptr) _rect = new SDL_Rect({x, y, rect.w, rect.h});
    Base::Render(renderer, _clip, _rect);
}

void Bullet::RenderBullets(SDL_Renderer* renderer, std::vector<Base*> &bullets)
{
    for(int i = 0; i < bullets.size(); i++){
        Base* bullet = bullets[i];
        if(bullet != nullptr){
            bullet->Render(renderer);
        }
    }
    ClearBullets(bullets);
}

void Bullet::ClearBullets(std::vector<Base*> &bullets)
{
    for(int i = 0; i < bullets.size(); i++){
        Base* bullet = bullets[i];
        if(bullet != nullptr){
            if(bullet->GetX() > GAME_SCREEN_WIDTH || bullet->GetX() < 0 || bullet->GetState() == CHARACTER_STATE::DEAD){
                bullets.erase(bullets.begin() + i);
                if(bullet != nullptr){
                    delete bullet;
                    bullet = nullptr;
                }
            }
        }
    }
}

