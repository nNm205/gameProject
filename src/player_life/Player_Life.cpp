#include "Player_Life.h"

Player_Life::Player_Life()
{

}

Player_Life::~Player_Life()
{

}

void Player_Life::addPos(const int &x)
{
    pos_list.push_back(x);
}

void Player_Life::Render(SDL_Renderer* renderer)
{
    if(numberOfLives == pos_list.size()){
        for(int i = 0; i < pos_list.size(); i++){
            SDL_Rect renderQuad = {pos_list[i], 5, 30, 30};
            Base::Render(renderer, nullptr, &renderQuad);
        }
    }
}

void Player_Life::Init(SDL_Renderer* renderer)
{
    LoadTexture("./assets/images/lives/alive.png", renderer);
    numberOfLives = 3;
    if(pos_list.size() > 0) pos_list.clear();
    addPos(5);
    addPos(40);
    addPos(75);
}

void Player_Life::Decrease()
{
    numberOfLives--;
    pos_list.pop_back();
}
