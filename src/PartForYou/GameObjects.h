#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"

class GameWorld;

//
// PlaneControlKeys
//

struct ControlKeys
{
    bool Left;
    bool Right;
    bool Up;
    bool Down;
    bool Fire1;
    bool Fire2;
};

// Move Mode
enum class MoveMode
{
    None,
    LeftDown,
    Down,
    RightDown,
};

//
// GameObject
//

class GameObject : public ObjectBase
{
public:
    GameObject(GameWorld* world, int imageID, int x, int y, int direction, int layer, double size);

    // return world
    GameWorld* world()const;

    // If the item is owned by the player, return true
    virtual bool IsPlayer()const;

    // if object is Plane, return true
    virtual bool IsPlane()const;

    // if object is Bullet, return true
    virtual bool IsBullet()const;

    // if object is Meteor, return true
    virtual bool IsMeteor()const;

    // if object is Item, return true
    virtual bool IsItem()const;

    // set object is Cleanable
    void SetMissing(bool value);

    // if object is Cleanable, return true
    bool IsMissing()const;

    // collision
    bool CollisionWith(GameObject* other)const;

    //virtual bool Collisionable()const;//....

    // destroy this object
    virtual void Destroy();

private:
    GameWorld* m_world;     // the world
    bool m_missing;
};

#endif // GAMEOBJECTS_H__
