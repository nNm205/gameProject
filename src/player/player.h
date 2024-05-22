#ifndef PLAYER_H
#define PLAYER_H

#include "../common/Common.h"
#include "../base/Base.h"

class Player : public Base {
private:
    std::vector<Base*> bullets;
    int hp;

    void HandleKeyDown(SDL_Event event, SDL_Renderer* renderer);
    void HandleKeyUp(SDL_Event event);
    void HandleMove();
    void HandleAttack(SDL_Renderer* renderer);
    void LoadTextureViaState(SDL_Renderer* renderer);
    void CreateBullet(SDL_Renderer* renderer);
public:
    Player();
    Player(SDL_Renderer* renderer);
    ~Player();

    std::vector<Base*> GetBullets(){
        return bullets;
    }

    void Render(SDL_Renderer* renderer);
    void HandleInputAction(SDL_Event event, SDL_Renderer* renderer);
};

#endif // PLAYER_H
