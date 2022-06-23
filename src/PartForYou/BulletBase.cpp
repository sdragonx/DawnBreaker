#include "BulletBase.h"

//
// BulletBase
//

BulletBase::BulletBase(PlaneBase* plane, int imageID, int x, int y, int direction, double size) :
    GameObject(plane->world(), imageID, x, y, direction, 0, size),
    m_plane(plane),
    m_damage()
{
}

PlaneBase* BulletBase::GetPlane()const
{
    return m_plane;
}

void BulletBase::SetDamage(int n)
{
    m_damage = n;
}

int BulletBase::GetDamage()const
{
    return m_damage;
}