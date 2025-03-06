#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#pragma once
#include "raylib.h"
#include <memory>
#include <vector>

class GameObject
{
    public:
    GameObject();
    ~GameObject();

    virtual void Update();
    virtual void Draw();
    virtual void Collision();

    bool isActive();
    bool SetActive(bool p_active);
    Vector2 GetPos();
    Vector2 SetPos(Vector2 p_position);
    int GetSize();
    int SetSize(int p_size);
    virtual void DrawSelf(int t_size);

    // m_position is target position
    Vector2 m_position;
    // p_position is current position
    Vector2 p_position;
    
    protected:
    int m_size;
    bool m_active;
};

#endif // GAME_OBJECT_H