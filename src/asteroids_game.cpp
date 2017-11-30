#include <random>
#include <iostream>
#include "asteroids_game.h"


AsteroidsGame::AsteroidsGame(Display &display)
: m_display(display), m_bullets(std::vector<Bullet>(3)) {

    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 );
    Mix_Volume(-1, 32);

    m_laser = Mix_LoadWAV("/home/james/C/asteroids/res/laser.wav");
    m_thruster = Mix_LoadWAV("/home/james/C/asteroids/res/ship_thruster2.wav");
    m_explosion = Mix_LoadWAV("/home/james/C/asteroids/res/explosion.wav");
    m_explosion2 = Mix_LoadWAV("/home/james/C/asteroids/res/explosion2.wav");

    initialise();
}

void AsteroidsGame::initialise() {

    if(!m_ship.isAlive()){
        m_ship.isAlive(true);
        m_ship.setPos(Vector2());
        m_ship.setVel(Vector2());
        m_score = 0;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> pos(-1.0, 1.0);
    std::uniform_real_distribution<> vel(-0.2, 0.2);
    std::uniform_real_distribution<> rot(0, 4.53786);
    std::uniform_real_distribution<> scale(0.1, 0.2);

    m_asteroids.clear();

    for (size_t i = 0; i < 5; i++) {

        bool asteroid_created = false;

        while (!asteroid_created) {
            Asteroid a(
                Vector2(pos(gen), pos(gen)),
                Vector2(vel(gen), vel(gen)),
                scale(gen),
                rot(gen)
            );

            if ((a.getPos() - m_ship.getPos()).mag() > 2 * a.getScale() + m_ship.getScale()) {
                asteroid_created = true;
                m_asteroids.push_back(a);
            }

        }

    }
}

void AsteroidsGame::input(const SDL_Event &event) {

    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                m_keyUp = true;
                break;
            case SDLK_LEFT:
                m_keyLeft = true;
                break;
            case SDLK_RIGHT:
                m_keyRight = true;
                break;
            case SDLK_SPACE:
                m_keyFire = true;
                break;
            case SDLK_ESCAPE:
                initialise();
                return;
                break;
        }
    }
    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                m_keyUp = false;
                break;
            case SDLK_LEFT:
                m_keyLeft = false;
                break;
            case SDLK_RIGHT:
                m_keyRight = false;
                break;
            case SDLK_SPACE:
                m_keyFire = false;
                break;
        }
    }
};

void AsteroidsGame::update(float timeDelta) {
    if (m_keyLeft) {
        m_ship.setRot(m_ship.getRot() - 5 * timeDelta);
    }
    if (m_keyRight) {
        m_ship.setRot(m_ship.getRot() + 5 * timeDelta);
    }
    if (m_keyUp) {
        if (m_ship.isAlive()) {
            Vector2 vel = m_ship.getVel() + Vector2(0, -0.7).rotate(m_ship.getRot()) * timeDelta;

            if (vel.mag() <= 1.5) {
                m_ship.setVel(vel);
                m_ship.selectFrame(1);
            }

            if (Mix_Playing(1) == 0) {
                Mix_PlayChannel(1, m_thruster, 0);
            }
        }

    }
    else {
        m_ship.selectFrame(0);
    }

    for(Bullet &bullet : m_bullets) {
        if (bullet.isAlive()) {
            bullet.updatePosition(timeDelta);
        }
        else if (m_keyFire && m_ship.isAlive()){
            bullet.fire(m_ship.getPos(), Vector2(0, -2).rotate(m_ship.getRot()));
            bullet.setRot(m_ship.getRot());
            m_keyFire = false;
            Mix_PlayChannel(0, m_laser, 0);
        }
    }


    size_t asteroids_count = m_asteroids.size();
    bool asteroids_alive = false;

    for (size_t i = 0; i < asteroids_count; i++) {

        Asteroid &asteroid = m_asteroids[i];
        asteroid.updatePosition(timeDelta);

        if (asteroid.isAlive()) {

            asteroids_alive = true;

            for(Bullet &bullet : m_bullets) {
                if (bullet.isAlive()) {
                    Vector2 dist = bullet.getPos() - asteroid.getPos();
                    if (dist.mag() <= 0.65 * asteroid.getScale()) {
                        asteroid.isAlive(false);
                        bullet.isAlive(false);

                        Mix_PlayChannel(-1, m_explosion, 0);
                        m_score += 100;

                        if (asteroid.getScale() < 0.07) continue;

                        Asteroid a = Asteroid(
                            asteroid.getPos() + asteroid.getVel() * 0.1,
                            asteroid.getVel().rotate(0.7) * 1.5,
                            asteroid.getScale()/2,
                            asteroid.getRot()
                        );

                        Asteroid b = Asteroid(
                            asteroid.getPos() - asteroid.getVel() * 0.1,
                            asteroid.getVel().rotate(-07) * 1.5,
                            asteroid.getScale()/2,
                            asteroid.getRot() * 1.5
                        );

                        m_asteroids.push_back(a);
                        m_asteroids.push_back(b);

                    }
                }
            }

            if (m_ship.isAlive() && ((asteroid.getPos() - m_ship.getPos()).mag() < 0.7 * asteroid.getScale() + m_ship.getScale())) {
                Mix_PlayChannel(-1, m_explosion2, 0);
                m_ship.isAlive(false);
            }

        }
    }

    if (!asteroids_alive) {
        if (!m_needInitalise) {
            m_needInitalise = true;
            m_nextInitialise = 3;
        }
        else {
            m_nextInitialise -= timeDelta;

            if (m_nextInitialise < 0) {
                m_needInitalise = false;
                initialise();
                return;
            }
        }
    }

    m_ship.updatePosition(timeDelta);
};

void AsteroidsGame::draw() {

    m_display.clear((SDL_Color){1, 0, 0, 0});
    if(m_ship.isAlive()) m_ship.drawObject(m_display);

    for(Bullet &bullet : m_bullets) {
        if (bullet.isAlive()) bullet.drawObject(m_display);
    }

    for(Asteroid &asteroid : m_asteroids) {
        if (asteroid.isAlive()) asteroid.drawObject(m_display);
    }

    m_display.drawText("SCORE: " + std::to_string(m_score), 12, 12);

    m_display.update();
};

AsteroidsGame::~AsteroidsGame() {
    Mix_FreeChunk(m_laser);
    Mix_FreeChunk(m_explosion);
    Mix_FreeChunk(m_explosion2);
    Mix_FreeChunk(m_thruster);
    Mix_CloseAudio();
};
