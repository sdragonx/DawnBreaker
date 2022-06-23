#pragma once

#include "BulletBase.h"

// RedBullet
class RedBullet : public BulletBase
{
public:
    RedBullet(PlaneBase* plane, int x, int y, int dir, int damage);

    void Update()override;
};
