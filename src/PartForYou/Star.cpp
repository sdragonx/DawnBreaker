#include "Star.h"


//
// Star
//

Star::Star(GameWorld* world, int x, int y, double size) :
    //GameObject(world, IMGID_STAR, x, y, randInt(0, 360), 4, size)
    GameObject(world, IMGID_STAR, x, y, 0, 4, size)
{

}

Star::~Star()
{

}

void Star::Update()
{
    if (this->IsMissing()) {
        return;
    }

    int x = GetX();
    int y = GetY();

    if (y < 0) {
        this->SetMissing(true);
        return;
    }

    y -= 1;
    this->MoveTo(x, y);
}
