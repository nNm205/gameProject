#ifndef BULLET_H
#define BULLET_H

#include "../common/Common.h"
#include "../base/Base.h"

class Bullet : public Base {
private:
    BULLET_TYPE bulletType;
    int damage;
    void loadBulletViaType(BULLET_TYPE _bulletType, SDL_Renderer* renderer);
public:
    Bullet();
    Bullet(BULLET_TYPE _bulletType, int _x, int _y, SDL_Renderer* renderer);
    ~Bullet();

    void Render(SDL_Renderer* renderer, SDL_Rect* clip = nullptr, SDL_Rect* rect = nullptr);
    static void RenderBullets(SDL_Renderer* renderer, std::vector<Base*> &bullets);
    static void ClearBullets(std::vector<Base*> &bullets);
};

#endif // BULLET_H
