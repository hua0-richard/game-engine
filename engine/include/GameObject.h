#pragma once
#include "raylib.h"

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
    virtual void DrawSelf();
    
    protected:
    Vector2 m_position;
    int m_size;
    bool m_active;


};