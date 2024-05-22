#ifndef DARK_H
#define DARK_H

#include "../common/Common.h"
#include "../enemy/Enemy.h"

class Dark : public Enemy {
private:
public:
    Dark(SDL_Renderer* renderer);
    ~Dark();

    void HandleAttackRandomly(SDL_Renderer* renderer);
};

#endif // DARK_H
