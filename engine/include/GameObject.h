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

    bool isActive();
    bool SetActive(bool p_active);
    Vector2 GetPos();
    Vector2 SetPos(Vector2 p_position);
    int GetSize();
    int SetSize(int p_size);
    virtual void DrawSelf(int t_size);

    Vector2 m_position;
    Vector2 p_position;
    
    protected:
    int m_size;
    bool m_active;


};