#pragma once

#include "ItemBase.h"


class PowerUpGoodie : public ItemBase
{
public:
    PowerUpGoodie(GameWorld* world, int x, int y);
    
protected:
    void OnCollision()override;
};
