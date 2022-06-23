#include "BlueBullet.h"
#include "GameWorld.h"

// BlueBullet
BlueBullet::BlueBullet(PlaneBase* plane, int x, int y, int damage, double size) :
    BulletBase(plane, IMGID_BLUE_BULLET, x, y, 0, size)
{
    this->SetDamage(damage);
}

BlueBullet::~BlueBullet()
{
    
}

void BlueBullet::Update()
{
    if (this->IsMissing()) {
        return;
    }

    int x = GetX();
    int y = GetY();

    if (y >= WINDOW_HEIGHT) {
        this->SetMissing(true);
        return;
    }

    // collision with enemy
    if (Collision()) {
        return;
    }

    y += 6;
    MoveTo(x, y);

    // collision with enemy again
    Collision();
}

bool BlueBullet::Collision()//3.
{
    for (auto obj : world()->Objects()) {
        if (obj->IsPlane() && !obj->IsPlayer()) {
            PlaneBase* plane = dynamic_cast<PlaneBase*>(obj);
            if (plane && !plane->IsMissing()) {
                if (this->CollisionWith(plane)) {
                    plane->AddHP(-this->GetDamage());
                    this->SetMissing(true);
                    return true;
                }
            }
        }
    }
    return false;
}
