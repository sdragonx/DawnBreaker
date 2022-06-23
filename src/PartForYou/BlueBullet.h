#pragma once

#include "BulletBase.h"

// BlueBullet
class BlueBullet : public BulletBase
{
public:
    BlueBullet(PlaneBase* plane, int x, int y, int damage, double size);
    ~BlueBullet()override;

    bool IsPlayer()const final override { return true; }

    void Update()override;

private:
    bool Collision();
};
