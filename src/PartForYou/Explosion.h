#pragma once

#include "GameObjects.h"

//
// Explosion
//

class Explosion : public GameObject
{
public:
    Explosion(GameWorld* world, int x, int y);
    ~Explosion()override;

    void Update()override;

private:
    int m_tick;
};
