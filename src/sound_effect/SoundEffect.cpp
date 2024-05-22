#include "SoundEffect.h"

Mix_Chunk* SoundEffect::attackSound = nullptr;

SoundEffect::SoundEffect()
{
    if(attackSound == nullptr){
        attackSound = LoadSound("./assets/sound_effects/attacking-sound.wav");
    }
}

SoundEffect::~SoundEffect()
{
    if(attackSound != nullptr){
        Mix_FreeChunk(attackSound);
        attackSound = nullptr;
    }
}

Mix_Chunk* SoundEffect::LoadSound(const char* path)
{
    Mix_Chunk* sound = Mix_LoadWAV(path);
    if(sound == nullptr){
        printf("Mix_LoadWAV Error: %s\n", Mix_GetError());
        return nullptr;
    }
    return sound;
}

void SoundEffect::PlaySound(const SOUND_EFFECT &soundEffect)
{
    switch(soundEffect){
    case SOUND_EFFECT::ATTACK:
        Mix_PlayChannel(-1, attackSound, 0);
        break;
    }
}

