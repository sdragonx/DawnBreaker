#pragma once

#include "GameObjects.h"

//
// Meteor
//

class Meteor : public GameObject
{
public:
    Meteor(GameWorld* world, int x, int y);

    bool IsPlayer()const final override { return true; }
    bool IsMeteor()const final override { return true; }

    void Update()override;

private:
    void Collision();
};
