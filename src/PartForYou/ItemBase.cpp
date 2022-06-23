#include "ItemBase.h"
#include "GameWorld.h"

ItemBase::ItemBase(GameWorld* world, int imageID, int x, int y) :
    GameObject(world, imageID, x, y, 0, 2, 0.5)
{

}

void ItemBase::Update()
{
    if (this->IsMissing()) {
        //printf("Item is missing\n");
        return;
    }

    int x = this->GetX();
    int y = this->GetY();

    if (y < 0) {
        this->SetMissing(true);
        return;
    }

    // collision with DawnBreaker
    if (Collision()) {
        return;
    }

    y -= 2;
    this->MoveTo(x, y);

    // collision with DawnBreaker again
    Collision();
}

bool ItemBase::Collision()
{
    if (this->CollisionWith(world()->GetDawnBreaker())) {
        this->OnCollision();        // virtual function
        this->SetMissing(true);
        return true;
    }
    return false;
}