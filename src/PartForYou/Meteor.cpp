#include "Meteor.h"
#include "GameWorld.h"
#include "PlaneBase.h"

//
// Meteor
//

Meteor::Meteor(GameWorld* world, int x, int y) :
    GameObject(world, IMGID_METEOR, x, y, 0, 1, 2.0)
{

}

void Meteor::Update()
{
    if (this->IsMissing()) {
        return;
    }

    int x = this->GetX();
    int y = this->GetY();

    if (y >= WINDOW_HEIGHT) {
        this->SetMissing(true);
        return;
    }

    // collision with enemy
    this->Collision();

    y += 2;
    this->SetDirection(GetDirection() + 5);
    this->MoveTo(x, y);

    // collision with enemy again
    this->Collision();
}

void Meteor::Collision()
{
    for (auto obj : world()->Objects()) {
        if (!obj->IsPlayer() && obj->IsPlane() && !obj->IsMissing()) {
            if (this->CollisionWith(obj)) {
                obj->Destroy();
            }
        }
    }
}
