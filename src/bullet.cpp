#include "bullet.h"

Bullet::Bullet()
: SpaceObject(Vector2(), Vector2()), m_isAlive(false) {
    m_lines = {
        { 0.0f, 0.00f },
        { 0.0f, 0.01f }
    };
}

void Bullet::fire(Vector2 pos, Vector2 vel) {
    setPos(pos);
    setVel(vel);
    m_aliveTime = 0.9f;
    m_isAlive = true;
}

void Bullet::updatePosition(float timeDelta) {
    SpaceObject::updatePosition(timeDelta);

    float time_left = m_aliveTime - timeDelta;

    if (time_left < 0) {
        m_isAlive = false;
        return;
    }
    m_aliveTime = time_left;
}

bool Bullet::isAlive() { return m_isAlive; }

void Bullet::isAlive(bool isAlive) { m_isAlive = isAlive; }
