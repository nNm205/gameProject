#include "src/common/Common.h"
#include "src/base/Base.h"
#include "src/player/player.h"
#include "src/bullet/Bullet.h"
#include "src/enemy/Enemy.h"
#include "src/dark/Dark.h"
#include "src/alien/Alien.h"
#include "src/eye/Eye.h"
#include "src/horn/Horn.h"
#include "src/explosion/Explosion.h"
#include "src/sound_effect/SoundEffect.h"
#include "src/player_life/Player_Life.h"
#include <SDL_ttf.h>

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Event event;
const char* lables[numberOfMenuItem] = {"Start Game", "Exit"};

bool isRunning = true;
int numberOfDie = 0;

Player_Life Lives;
Base* LoadMenu();
Base* LoadBackground();
bool Initialize();
void Cleanup();
void CreateEnemies(std::vector<Enemy*> &enemies, SDL_Renderer* renderer);
bool overlap(const SDL_Rect &r1, const SDL_Rect &r2);
void HandleCollision(Player* player, std::vector<Enemy*> &enemies, std::vector<Explosion*> &explosions);

int RenderMenu(SDL_Renderer* renderer, TTF_Font* font)
{
    int x, y;
    SDL_Surface* menus[numberOfMenuItem];
    bool selected[numberOfMenuItem] = {0, 0};
    SDL_Color color[2] = {{255, 255, 255}, {255, 0, 0}};

    menus[0] = TTF_RenderText_Solid(font, "Start Game", color[0]);
    menus[0]->w = 120;
    menus[1] = TTF_RenderText_Solid(font, "Exit", color[0]);

    SDL_Rect posMenu[numberOfMenuItem];
    posMenu[0].x = GAME_SCREEN_WIDTH / 2 - menus[0]->w*3;
    posMenu[0].y = GAME_SCREEN_HEIGHT / 2 + menus[0]->h;
    posMenu[1].x = GAME_SCREEN_WIDTH / 2 + menus[1]->w*3 + 100;
    posMenu[1].y = GAME_SCREEN_HEIGHT / 2 + menus[0]->h;

    SDL_Event event;
    while(1){
        Uint32 frameStart = SDL_GetTicks();
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                for(int i = 0; i < numberOfMenuItem; i++){
                    SDL_FreeSurface(menus[i]);
                }
                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for(int i = 0; i < numberOfMenuItem; i++){
                    if(x >= posMenu[i].x && x <= posMenu[i].x + posMenu[i].x + posMenu[i].w
                    && y >= posMenu[i].y && y <= posMenu[i].y + posMenu[i].y + posMenu[i].h)
                    {
                        if(selected[i] == 0){
                            selected[i] = 1;
                            SDL_FreeSurface(menus[i]);
                            if(i == 0) menus[i] = TTF_RenderText_Solid(font, "Start Game", color[1]);
                            else menus[i] = TTF_RenderText_Solid(font, "Exit", color[1]);
                        }
                    }
                    else{
                        if(selected[i] == 1){
                            selected[i] = 0;
                            SDL_FreeSurface(menus[i]);
                            if(i == 0) menus[i] = TTF_RenderText_Solid(font, "Start Game", color[0]);
                            else menus[i] = TTF_RenderText_Solid(font, "Exit", color[0]);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for(int i = 0; i < numberOfMenuItem; i++){
                    if(x >= posMenu[i].x && x <= posMenu[i].x + posMenu[i].x + posMenu[i].w
                    && y >= posMenu[i].y && y <= posMenu[i].y + posMenu[i].y + posMenu[i].h)
                    {
                        SDL_FreeSurface(menus[i]);
                        return i;
                    }
                }
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_SPACE){
                    for(int i = 0; i < numberOfMenuItem; i++){
                        SDL_FreeSurface(menus[i]);
                    }
                    return 0;
                }
            }
        }
        for(int i = 0; i < numberOfMenuItem; i++){
            SDL_Texture* menuTexture = SDL_CreateTextureFromSurface(renderer, menus[i]);
            SDL_Rect rect = {posMenu[i].x, posMenu[i].y, menus[i]->w, menus[i]->h};
            SDL_RenderCopy(renderer, menuTexture, nullptr, &rect);
            SDL_RenderPresent(renderer);
        }
        int frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < GAME_TICKS_PER_FRAME){
            SDL_Delay(GAME_TICKS_PER_FRAME - frameTime);
        }
    }
}

int main(int argc, char* argv[])
{
    /// Initialize
    if(!Initialize()){
        printf("Failed to initialize!\n");
        return -1;
    }

    Base* Menu = LoadMenu();
    Menu->Render(renderer);
    SDL_RenderPresent(renderer);

    TTF_Font* font = TTF_OpenFont("./assets/font/Consolas.ttf", 20);

    int option = RenderMenu(renderer, font);
    if(option == 1) isRunning = false;

    Base* background = LoadBackground();
    Player* player = new Player(renderer);
    std::vector<Enemy*> enemies;
    std::vector<Explosion*> explosions;
    Lives.Init(renderer);

    /// Main Game Loop
    while(isRunning){
        Uint32 frameStart = SDL_GetTicks();

        /// Event Handling
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                isRunning = false;
            }
            /// Movement of player
            player->HandleInputAction(event, renderer);
        }

        /// Clear the screen
        SDL_RenderClear(renderer);

        /// Draw here
        background->Render(renderer);
        Lives.Render(renderer);
        player->Render(renderer);
        CreateEnemies(enemies, renderer);
        HandleCollision(player, enemies, explosions);

        /// Update the screen
        SDL_RenderPresent(renderer);

        int frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < GAME_TICKS_PER_FRAME){
            SDL_Delay(GAME_TICKS_PER_FRAME - frameTime);
        }
    }

    /// Destroy and Exit
    Cleanup();
    return 0;
}

bool Initialize()
{
    /// Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    /// Initialize IMG
    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0){
        printf("IMG_Init Error: %s\n", IMG_GetError());
        return false;;
    }

    /// Initialize Mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        printf("AUDIO_Init Error: %s\n", Mix_GetError());
        return false;
    }

    /// Initialize TTF
    TTF_Init();

    /// Creating window
    window = SDL_CreateWindow(GAME_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return false;
    }

    /// Creating renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

Base* LoadBackground()
{
    Base* background = new Base();
    background->LoadTexture("./assets/images/background/background8.png", renderer);
    SDL_Rect rect = {0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT};
    background->setRect(rect);
    return background;
}

Base* LoadMenu()
{
    Base* menu = new Base();
    menu->LoadTexture("./assets/images/menu/Menu_.png", renderer);
    SDL_Rect rect = {0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT};
    menu->setRect(rect);
    return menu;
}

void CreateEnemies(std::vector<Enemy*> &enemies, SDL_Renderer* renderer)
{
    int currentTime = SDL_GetTicks();
    if(currentTime % 2000 < 15 && enemies.size() <= 10){
        int randomType = rand() % 4;
        switch(randomType){
        case 0:
            enemies.push_back(new Dark(renderer));
            break;
        case 1:
            enemies.push_back(new Alien(renderer));
            break;
        case 2:
            enemies.push_back(new Horn(renderer));
            break;
        case 3:
            enemies.push_back(new Eye(renderer));
            break;
        }
    }

    for(auto &enemy : enemies) enemy->HandleRandomMove(renderer);
    for(int i = 0; i < enemies.size(); i++){
        Enemy* enemy = enemies[i];
        if(enemy->GetHP() <= 0){
            enemies.erase(enemies.begin() + i);
            if(enemy != nullptr){
                delete enemy;
                enemy = nullptr;
            }
        }
    }
}

bool overlap(int x1, int y1, const SDL_Rect& r1, int x2, int y2, const SDL_Rect& r2)
{
    int L1 = x1, R1 = x1 + r1.w, T1 = y1, B1 = y1 + r1.h;
    int L2 = x2, R2 = x2 + r2.w, T2 = y2, B2 = y2 + r2.h;
    // Case 1: size object 1 < size object 2
    if(L1 > L2 && L1 < R2 && T1 > T2 && T1 < B2) return true;
    if(L1 > L2 && L1 < R2 && B1 > T2 && B1 < B2) return true;
    if(R1 > L2 && R1 < R2 && T1 > T2 && T1 < B2) return true;
    if(R1 > L2 && R1 < R2 && B1 > T2 && B1 < B2) return true;
    // Case 2: size object 1 < size object 2
    if(L2 > L1 && L2 < R1 && T2 > T1 && T2 < B1) return true;
    if(L2 > L1 && L2 < R1 && B2 > T1 && B2 < B1) return true;
    if(R2 > L1 && R2 < R1 && T2 > T1 && T2 < B1) return true;
    if(R2 > L1 && R2 < R1 && B2 > T1 && B2 < B1) return true;
    // Case 3: size object 1 = size object 2
    if(T1 == T2 && R1 == R2 && B1 == B2 && L1 == L2) return true;
    return false;
}

void HandleCollision(Player* player, std::vector<Enemy*> &enemies, std::vector<Explosion*> &explosions)
{
    for(int i = 0; i < enemies.size(); i++){
        // collision between player and enemy
        Enemy* enemy = enemies[i];
        if(overlap(player->GetX(), player->GetY(), player->GetRect(), enemy->GetX(), enemy->GetY(), enemy->GetRect()))
        {
            numberOfDie++;
            enemies.erase(enemies.begin() + i);
            if(numberOfDie <= 2)
            {
                SDL_Delay(1000);
                Lives.Decrease();
                Lives.Render(renderer);
            }
            else{
                std::cout << "Game Over!!!" << '\n';
                exit(0);
            }
        }
        // collision between bullet of player and enemy
        std::vector<Base*> bulletOfPlayer = player->GetBullets();
        for(int i = 0; i < bulletOfPlayer.size(); i++){
            Base* bullet = bulletOfPlayer[i];
            if(overlap(bullet->GetX(), bullet->GetY(), bullet->GetRect(), enemy->GetX(), enemy->GetY(), enemy->GetRect())){
                explosions.push_back(new Explosion(enemy->GetX(), bullet->GetY(), renderer));
                bullet->SetState(CHARACTER_STATE::DEAD);
                enemy->SetHP(enemy->GetHP() - 100);
            }
        }
        // collision between bullet of enemy and player
        std::vector<Base*> bulletOfEnemy = enemy->GetBullets();
        for(int i = 0; i < bulletOfEnemy.size(); i++){
            Base* bullet = bulletOfEnemy[i];
            if(overlap(bullet->GetX(), bullet->GetY(), bullet->GetRect(), player->GetX(), player->GetY(), player->GetRect())){
                bullet->SetState(CHARACTER_STATE::DEAD);
                numberOfDie++;
                if(numberOfDie <= 2)
                {
                    SDL_Delay(1000);
                    Lives.Decrease();
                    Lives.Render(renderer);
                }
                else{
                    std::cout << "Game Over!!!" << '\n';
                    exit(0);
                }
            }
        }
    }

    for(auto &explosion : explosions) explosion->Render(renderer);
    for(int i = 0; i < explosions.size(); i++){
        Explosion* explosion = explosions[i];
        if(explosion->GetState() == CHARACTER_STATE::DEAD){
            explosions.erase(explosions.begin() + i);
            if(explosion != nullptr){
                delete explosion;
                explosion = nullptr;
            }
        }
    }
}

void Cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
