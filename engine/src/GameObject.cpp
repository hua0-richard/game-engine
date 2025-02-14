#include "GameObject.h"


GameObject::GameObject(Vector2 p_pos, int p_size)
{
    m_active = true;
    m_position = p_pos;
    m_size = p_size;
}

void GameObject::Update()
{
}

void GameObject::Draw()
{
}

bool GameObject::isActive()
{
    return m_active;
}
bool GameObject::SetActive(bool p_active)
{
    m_active = p_active;
}

Vector2 GameObject::GetPos()
{
    return m_position;
}

Vector2 GameObject::SetPos(Vector2 p_position)
{
    m_position = p_position;
}

int GameObject::GetSize()
{
   return m_size;
}

int GameObject::SetSize(int p_size)
{
    m_size = p_size;
}
