#pragma once

#include <SDL2/SDL_mixer.h>
#include "display.h"
#include "asteroid.h"
#include "bullet.h"
#include "ship.h"

class AsteroidsGame {
private:
    Display &m_display;
    Ship m_ship;
    std::vector<Asteroid> m_asteroids;
    std::vector<Bullet> m_bullets;

    bool m_keyUp    = false;
    bool m_keyLeft  = false;
    bool m_keyRight = false;
    bool m_keyFire  = false;

    Mix_Chunk *m_laser;
    Mix_Chunk *m_thruster;
    Mix_Chunk *m_explosion;
    Mix_Chunk *m_explosion2;

    float m_nextInitialise;
    bool m_needInitalise = false;

    int m_score = 0;

    void initialise();

public:
    AsteroidsGame(Display &display);
    void input(const SDL_Event &event);
    void update(float timeDelta);
    void draw();
    virtual ~AsteroidsGame ();
};
