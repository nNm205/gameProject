#ifndef ENEMY_H
#define ENEMY_H

#include "../common/Common.h"
#include "../base/Base.h"

class Enemy : public Base {
protected:
    std::vector<Base*> bullets;
    ENEMY_TYPE type;
    int hp;
    int deviation;
public:
    Enemy();
    ~Enemy();

    std::vector<Base*> GetBullets(){
        return bullets;
    }
    void LoadTextureViaType(SDL_Renderer* renderer);
    void HandleMove();
    void Render(SDL_Renderer* renderer);
    void HandleRandomMove(SDL_Renderer* renderer);
    virtual void HandleAttackRandomly(SDL_Renderer* renderer){};

    void SetHP(int _hp){
        hp = _hp;
    }
    int GetHP(){
        return hp;
    }
};

#endif // ENEMY_H
