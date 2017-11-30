#include "asteroid.h"

Asteroid::Asteroid(Vector2 pos, Vector2 vel, float scale, float rot)
: SpaceObject(pos, vel, scale, rot) {

    m_lines = {
        { 0.00f, -0.70f },
        { 0.30f, -0.30f },
        { 0.30f, -0.30f },
        { 0.70f, -0.50f },
        { 0.70f, -0.50f },
        { 0.75f,  0.00f },
        { 0.75f, -0.00f },
        { 0.70f,  0.70f },
        { 0.70f,  0.70f },
        { 0.00f,  0.65f },
        { 0.00f,  0.65f },
        {-0.30f,  0.50f },
        {-0.30f,  0.50f },
        {-0.70f,  0.40f },
        {-0.70f,  0.40f },
        {-0.70f,  0.00f },
        {-0.70f,  0.00f },
        {-0.70f, -0.50f },
        {-0.70f, -0.50f },
        { 0.00f, -0.70f }
    };
}

bool Asteroid::isAlive() {
    return m_isAlive;
}

void Asteroid::isAlive(bool isAlive) {
    m_isAlive = isAlive;
}
