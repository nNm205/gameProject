#ifndef ALIEN_H
#define ALIEN_H

#include "../common/Common.h"
#include "../enemy/Enemy.h"

class Alien : public Enemy {
private:
public:
    Alien(SDL_Renderer* renderer);
    ~Alien();

    void HandleAttackRandomly(SDL_Renderer* renderer);
};

#endif // ALIEN_H
