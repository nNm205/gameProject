#include "Enemy.h"
#include "../bullet/Bullet.h"

Enemy::Enemy()
{
    type = ENEMY_TYPE::ALIEN;
    hp = 0;
    deviation = 0;
    x = -1;
}

Enemy::~Enemy()
{
    Free();
}

void Enemy::HandleMove()
{
    if(inputType.up && y < 0) inputType.up = false;
    if(inputType.down && y > GAME_SCREEN_HEIGHT - heightFrame) inputType.down = false;
    if(inputType.left && x < -widthFrame) x = GAME_SCREEN_WIDTH;

    if(inputType.up) y += deviation;
    if(inputType.down) y += deviation;
    if(inputType.left) x += speed;
}

void Enemy::LoadTextureViaType(SDL_Renderer* renderer)
{
    if(type == 0) LoadTexture("./assets/images/enemy/alien_.png", renderer);
    if(type == 1) LoadTexture("./assets/images/enemy/dark_.png", renderer);
    if(type == 2) LoadTexture("./assets/images/enemy/eye_.png", renderer);
    if(type == 3) LoadTexture("./assets/images/enemy/horn_.png", renderer);
}

void Enemy::Render(SDL_Renderer* renderer)
{
    if(state == CHARACTER_STATE::DEAD){
        state = CHARACTER_STATE::FLYING;
        if(texture != nullptr){
            delete texture;
            texture = nullptr;
        }
    }

    LoadTextureViaType(renderer);
    HandleMove();
    Bullet::RenderBullets(renderer, bullets);
    SDL_Rect renderQuad = {x, y, widthFrame, heightFrame};
    Base::Render(renderer, nullptr, &renderQuad);
}

void Enemy::HandleRandomMove(SDL_Renderer* renderer)
{
    int currentTime = SDL_GetTicks();
    if(x == -1){
        inputType.left = true;
        speed = -3;
        x = GAME_SCREEN_WIDTH;
        y = rand() % (GAME_SCREEN_HEIGHT - heightFrame);
        deviation = 0;
    }
    if(currentTime % 2000 < 10){
        int randomMove = rand() % 3;
        switch(randomMove){
        case 0:
            inputType.left = true;
            inputType.right = false;
            speed = -3;
            if(y > GAME_SCREEN_HEIGHT - heightFrame - 80){
                deviation = -2;
                inputType.up = true;
                inputType.down = false;
            }
            else if(y < 30){
                deviation = 2;
                inputType.up = false;
                inputType.down = true;
            }
            break;
        case 1:
            inputType.up = true;
            inputType.down = false;
            deviation = -2;
            if(y < 30){
                deviation = 2;
                inputType.down = true;
                inputType.up = false;
            }
            break;
        case 2:
            inputType.up = false;
            inputType.down = true;
            deviation = 2;
            if(y > GAME_SCREEN_HEIGHT - heightFrame - 80){
                deviation = -2;
                inputType.up = false;
                inputType.down = true;
            }
            break;
        default:
            break;
        }
    }
    Render(renderer);
    HandleAttackRandomly(renderer);
}





























