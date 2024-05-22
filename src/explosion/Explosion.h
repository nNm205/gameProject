#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "../base/Base.h"
#include "../common/Common.h"

const int EXPLOSION_WIDTH = 54;
const int EXPLOSION_HEIGHT = 48;
const int NUMBER_OF_FRAMES = 10;

class Explosion : public Base {
private:
    int currentFrame;
    SDL_Rect frameClip[NUMBER_OF_FRAMES];
public:
    Explosion(int x, int y, SDL_Renderer* renderer);
    ~Explosion();

    void SetFrameClip();
    void SetCurrentFrame(const int &_currentFrame){
        currentFrame = _currentFrame;
    }
    void Render(SDL_Renderer* renderer);
};

#endif // EXPLOSION_H
