#pragma once

#include "space_object.h"

class Bullet : public SpaceObject {
private:
    float m_aliveTime;
    bool m_isAlive;

public:
    Bullet();
    void fire(Vector2 pos, Vector2 vel);
    void updatePosition(float timeDelta);
    bool isAlive();
    void isAlive(bool isAlive);
};
