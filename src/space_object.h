#pragma once

#include <vector>
#include "vector2.h"
#include "display.h"

class SpaceObject {
protected:
    Vector2 m_pos;      // Position
    Vector2 m_vel;      // Velocity
    float m_scale;      // Scale
    float m_rot;        // rotation

    std::vector<Vector2> m_lines;

public:
    SpaceObject (Vector2 pos, Vector2 vel, float scale=1.0f, float rot=0);
    virtual void drawObject(Display &display);
    virtual void updatePosition(float timeDelta);
    
    void setPos(Vector2 pos);
    Vector2 getPos();

    void setVel(Vector2 vel);
    Vector2 getVel();

    void setScale(float scale);
    float getScale();

    void setRot(float rot);
    float getRot();

    virtual ~SpaceObject ();
};
