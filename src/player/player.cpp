#include "player.h"
#include "../sound_effect/SoundEffect.h"
#include "../bullet/Bullet.h"

Player::Player()
{
    widthFrame = 0;
    heightFrame = 0;
}

Player::Player(SDL_Renderer* renderer)
{
    widthFrame = 0;
    heightFrame = 0;

    x = 100;
    y = 100;

    rect.x = x;
    rect.y = y;
    speed = 10;
    hp = 100;

    LoadTexture("./assets/images/player/chicken.png", renderer);
}

Player::~Player()
{
    Free();
}

void Player::Render(SDL_Renderer* renderer)
{
    LoadTextureViaState(renderer);
    HandleMove();

    SDL_Rect renderQuad = {x, y, widthFrame, heightFrame};
    Bullet::RenderBullets(renderer, bullets);
    Base::Render(renderer, nullptr, &renderQuad);
}

void Player::HandleKeyDown(SDL_Event event, SDL_Renderer* renderer)
{
    switch(event.key.keysym.sym){
    /// up
    case SDLK_UP:
        inputType.up = true;
        break;
    /// down
    case SDLK_DOWN:
        inputType.down = true;
        break;
    /// left
    case SDLK_LEFT:
        inputType.left = true;
        break;
    /// right
    case SDLK_RIGHT:
        inputType.right = true;
        break;
    /// attack
    case SDLK_SPACE:
        HandleAttack(renderer);
        break;
    default:
        break;
    }
}

void Player::HandleKeyUp(SDL_Event event)
{
    switch(event.key.keysym.sym){
    /// up
    case SDLK_UP:
        inputType.up = false;
        break;
    /// down
    case SDLK_DOWN:
        inputType.down = false;
        break;
    /// left
    case SDLK_LEFT:
        inputType.left = false;
        break;
    /// right
    case SDLK_RIGHT:
        inputType.right = false;
        break;
    ///
    case SDLK_SPACE:
        state = CHARACTER_STATE::FLYING;
        break;
    default:
        break;
    }
}

void Player::HandleInputAction(SDL_Event event, SDL_Renderer* renderer)
{
    if(event.type == SDL_KEYDOWN) HandleKeyDown(event, renderer);
    if(event.type == SDL_KEYUP) HandleKeyUp(event);
}


void Player::HandleMove()
{
    if(inputType.up && y < 0) inputType.up = false;
    if(inputType.down && y > GAME_SCREEN_HEIGHT - heightFrame) inputType.down = false;
    if(inputType.left && x < 0) inputType.left = false;
    if(inputType.right && x > GAME_SCREEN_WIDTH - widthFrame) inputType.right = false;
    Base::HandleMove();
}

void Player::HandleAttack(SDL_Renderer* renderer)
{
    if(state == ATTACKING) return;
    state = ATTACKING;
    CreateBullet(renderer);
    SoundEffect::PlaySound(SOUND_EFFECT::ATTACK);
}

void Player::LoadTextureViaState(SDL_Renderer* renderer)
{
    if(state == CHARACTER_STATE::ATTACKING){
        LoadTexture("./assets/images/player/chicken_shoot.png", renderer);
    }
    else{
        LoadTexture("./assets/images/player/chicken.png", renderer);
    }
}

void Player::CreateBullet(SDL_Renderer *renderer){
    bullets.push_back(new Bullet(BULLET_TYPE::PLAYER_BULLET, x + widthFrame, y+10, renderer));
}
