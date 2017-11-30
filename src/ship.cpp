#include "ship.h"

Ship::Ship(Vector2 pos, Vector2 vel, float scale, float rot)
: SpaceObject(pos, vel, scale, rot) {

    // Ship
    m_frame1 = {
        { 0.00f, -1.00f },
        { 0.80f,  0.80f },
        { 0.60f,  0.35f },
        {-0.60f,  0.35f },
        {-0.80f,  0.80f },
        { 0.00f, -1.00f }
    };
    // Ship with thruster activated
    m_frame2 = {
        { 0.00f, -1.00f },
        { 0.80f,  0.80f },
        { 0.60f,  0.35f },
        {-0.60f,  0.35f },
        { 0.30f,  0.35f },
        { 0.00f,  1.20f },
        {-0.30f,  0.35f },
        { 0.00f,  1.20f },
        {-0.80f,  0.80f },
        { 0.00f, -1.00f }
    };

    selectFrame(0);
}

void Ship::selectFrame(char i) {
    if (i==0) {
        m_lines.assign(m_frame1.begin(), m_frame1.end());
    }
    if (i==1) {
        m_lines.assign(m_frame2.begin(), m_frame2.end());
    }
}

bool Ship::isAlive() {
    return m_isAlive;
}

void Ship::isAlive(bool isAlive) {
    m_isAlive = isAlive;
}

Ship::~Ship() {};
