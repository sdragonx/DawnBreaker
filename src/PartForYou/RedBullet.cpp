#include "RedBullet.h"
#include "GameWorld.h"

// RedBullet
RedBullet::RedBullet(PlaneBase* plane, int x, int y, int dir, int damage) :
    BulletBase(plane, IMGID_RED_BULLET, x, y, dir, 0.5)
{
    this->SetDamage(damage);
}

void RedBullet::Update()
{
    if (this->IsMissing()) {//1.
        return;
    }

    int x = GetX();
    int y = GetY();

    if (y < 0) {//2.
        this->SetMissing(true);
        return;
    }

    // collision with DawnBreaker
    PlaneBase* plane = world()->GetDawnBreaker();
    if (this->CollisionWith(plane)) {
        plane->AddHP(-this->GetDamage());
        this->SetMissing(true);
        return;
    }

    switch (this->GetDirection()) {
    case 180:
        y -= 6;
        break;
    case 162:
        x += 2;
        y -= 6;
        break;
    case 198:
        x -= 2;
        y -= 6;
        break;
    default:
        break;
    }    
    MoveTo(x, y);

    // collision with DawnBreaker again
    if (this->CollisionWith(plane)) {
        plane->AddHP(-this->GetDamage());
        this->SetMissing(true);
    }
}



/*switch (GetMoveMode()) {
case MoveMode::Down:
    this->SetDirection(180);
    break;
case MoveMode::LeftDown:
    this->SetDirection(198);
    break;
case MoveMode::RightDown:
    this->SetDirection(162);
    break;
default:
    break;
}*/