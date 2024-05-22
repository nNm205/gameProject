#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include "../common/Common.h"

class SoundEffect {
private:
    static Mix_Chunk* attackSound;
    static Mix_Chunk* LoadSound(const char* path);

public:
    SoundEffect();
    ~SoundEffect();

    static void PlaySound(const SOUND_EFFECT &soundEffect);
};

#endif // SOUNDEFFECT_H











/*#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

#include "../common/Common.h"

class SoundEffect {
private:
    static Mix_Chunk* attackSound;
    static Mix_Chunk* LoadSound(const char* path);
public:
    SoundEffect();
    ~SoundEffect();

    static void PlaySound(const SOUND_EFFECT &soundEffect);
};

#endif // SOUND_EFFECT_H
*/
