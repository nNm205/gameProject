#ifndef HORN_H
#define HORN_H

#include "../common/Common.h"
#include "../enemy/Enemy.h"

class Horn : public Enemy {
private:
public:
    Horn(SDL_Renderer* renderer);
    ~Horn();

    void HandleAttackRandomly(SDL_Renderer* renderer);
};

#endif // DARK_H
