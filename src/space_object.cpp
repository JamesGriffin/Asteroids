#include <cmath>
#include "space_object.h"

SpaceObject::SpaceObject(Vector2 pos, Vector2 vel, float scale, float rot)
: m_pos(pos), m_vel(vel), m_scale(scale), m_rot(rot) {}

void SpaceObject::drawObject(Display &display) {
    int width = display.getWidth();
    int height = display.getHeight();

    int half_width = width / 2;
    int half_height = height / 2;

    float ratio = (float)height / width;

    // For each line that makes up the object graphic
    for (size_t i = 0; i < m_lines.size(); i+=2) {

        // Apply rotation
        float x1 = m_lines[i].x * std::cos(m_rot) - m_lines[i].y * std::sin(m_rot);
        float y1 = m_lines[i].x * std::sin(m_rot) + m_lines[i].y * std::cos(m_rot);

        float x2 = m_lines[i + 1].x * std::cos(m_rot) - m_lines[i + 1].y * std::sin(m_rot);
        float y2 = m_lines[i + 1].x * std::sin(m_rot) + m_lines[i + 1].y * std::cos(m_rot);

        // Convert normalised coordinates to pixel coordinates
        x1 = (ratio * m_scale * x1 + m_pos.x) * half_width + half_width;
        y1 = (m_scale * y1 + m_pos.y) * half_height + half_height;

        x2 = (ratio * m_scale * x2 + m_pos.x) * half_width + half_width;
        y2 = (m_scale * y2 + m_pos.y) * half_height + half_height;

        display.drawLine(std::ceil(x1), std::ceil(y1), std::ceil(x2), std::ceil(y2), 0xFFFFFFFF);
    }
}

void SpaceObject::updatePosition(float timeDelta) {

    Vector2 pos = m_pos + m_vel * timeDelta;

    // Wrap-around screen
    if (pos.x < -1) pos.x = pos.x + 2;
    if (pos.x >= 1) pos.x = pos.x - 2;
    if (pos.y < -1) pos.y = pos.y + 2;
    if (pos.y >= 1) pos.y = pos.y - 2;

    m_pos = pos;
}

void SpaceObject::setPos(Vector2 pos) { m_pos = pos; }

Vector2 SpaceObject::getPos() { return m_pos; }

void SpaceObject::setVel(Vector2 vel) { m_vel = vel; }

Vector2 SpaceObject::getVel() { return m_vel; }

void SpaceObject::setScale(float scale) { m_scale = scale; }

float SpaceObject::getScale() { return m_scale; }

void SpaceObject::setRot(float rot) { m_rot = rot; }

float SpaceObject::getRot() { return m_rot; }

SpaceObject::~SpaceObject() {}
