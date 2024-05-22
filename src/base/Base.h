#ifndef BASE_H
#define BASE_H

#include "../common/Common.h"

class Base {
protected:
    int x, y;
    SDL_Rect rect;
    SDL_Texture* texture;

    int widthFrame, heightFrame;
    CHARACTER_STATE state;

    int speed;
    Input inputType;
public:
    Base();
    ~Base();

    void setRect(const SDL_Rect &_rect){
        rect = _rect;
    }
    SDL_Rect GetRect(){
        return rect;
    }
    void SetX(int _x){
        x = _x;
    }
    void SetY(int _y){
        y = _y;
    }
    int GetX(){
        return x;
    }
    int GetY(){
        return y;
    }

    void SetState(const CHARACTER_STATE &_state){
        state = _state;
    }
    CHARACTER_STATE GetState(){
        return state;
    }

    void Free();
    bool LoadTexture(const char* path, SDL_Renderer* renderer);
    virtual void Render(SDL_Renderer* renderer,  SDL_Rect* clip = nullptr, SDL_Rect* rect = nullptr);
    SDL_Surface* LoadSurface(const char* path);
    void HandleMove();
};

#endif // BASE_H

