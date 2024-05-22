#ifndef PLAYER_LIFE_H
#define PLAYER_LIFE_H

#include "../base/Base.h"
#include "../common/Common.h"

class Player_Life : public Base {
private:
    int numberOfLives;
    std::vector<int> pos_list;
public:
    Player_Life();
    ~Player_Life();
    void SetNumberOfLives(int _numberOfLives){
        numberOfLives = _numberOfLives;
    }
    void addPos(const int &x);
    void Render(SDL_Renderer* renderer);
    void Init(SDL_Renderer* renderer);
    void Decrease();
};
#endif // PLAYER_LIFE_H
