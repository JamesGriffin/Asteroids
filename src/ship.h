#pragma once

#include "space_object.h"

class Ship : public SpaceObject {
private:
    std::vector<Vector2> m_frame1;
    std::vector<Vector2> m_frame2;
    bool m_isAlive = true;
public:
    Ship(Vector2 pos=Vector2(), Vector2 vel=Vector2(), float scale=0.03f, float rot=0);
    void selectFrame(char i);
    bool isAlive();
    void isAlive(bool isAlive);
    virtual ~Ship();
};
