#include "GameObjects.h"

GameObject::GameObject(GameWorld* world, int imageID, int x, int y, int direction, int layer, double size) :
    ObjectBase(imageID, x, y, direction, layer, size),
    m_world(world),
    m_missing(false)
{

}

// return world
GameWorld* GameObject::world()const
{
    return m_world;
}

// If the item is owned by the player, return true
bool GameObject::IsPlayer()const
{
    return false;
}

// if object is Plane, return true
bool GameObject::IsPlane()const
{
    return false;
}

// if object is bullet, return true;
bool GameObject::IsBullet()const
{
    return false;
}

// if object is meteor, return true
bool GameObject::IsMeteor()const
{
    return false;
}

// if object is Item, return true
bool GameObject::IsItem()const
{
    return false;
}

// set object is Cleanable
void GameObject::SetMissing(bool value)
{
    m_missing = value;
}

// if object is Cleanable, return true
bool GameObject::IsMissing()const
{
    return m_missing;
}

// destroy this object
void GameObject::Destroy()
{
    this->SetMissing(true);
}

// collision
bool GameObject::CollisionWith(GameObject* other)const
{
    // pos x1, y1, x2, y2
    // size s1, s2
    // d = sqrt(...)
    // d < 30.0 * (s1 + s2)

    int w = other->GetX() - this->GetX();
    int h = other->GetY() - this->GetY();
    double d = sqrt(w * w + h * h);
    double s1 = this->GetSize();
    double s2 = other->GetSize();

    return d < 30.0 * (s1 + s2);
}