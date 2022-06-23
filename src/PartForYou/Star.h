#pragma once

#include "GameObjects.h"

//
// Star
//

class Star : public GameObject
{
public:
    Star(GameWorld* world, int x, int y, double size);
    ~Star()override;

    void Update()override;
};
