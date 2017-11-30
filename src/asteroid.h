#pragma once

#include "space_object.h"

class Asteroid : public SpaceObject {
private:
    bool m_isAlive = true;
public:
    Asteroid(Vector2 pos, Vector2 vel, float scale=1.0f, float rot=0);
    bool isAlive();
    void isAlive(bool isAlive);
};
