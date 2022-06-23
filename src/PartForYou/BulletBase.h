#pragma once

#include "PlaneBase.h"

//
// BulletBase
//

class BulletBase : public GameObject
{
public:
    BulletBase(PlaneBase* plane, int imageID, int x, int y, int direction, double size);

    bool IsBullet()const override final { return true; }

    PlaneBase* GetPlane()const;

    void SetDamage(int n);
    int GetDamage()const;

private:
    PlaneBase* m_plane;
    int m_damage;
};
