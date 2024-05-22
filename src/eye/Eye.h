#ifndef EYE_H
#define EYE_H

#include "../common/Common.h"
#include "../enemy/Enemy.h"

class Eye : public Enemy {
private:
public:
    Eye(SDL_Renderer* renderer);
    ~Eye();

    void HandleAttackRandomly(SDL_Renderer* renderer);
};

#endif // EYE_H
