#pragma once

#include "ItemBase.h"


class MeteorGoodie : public ItemBase
{
public:
    MeteorGoodie(GameWorld* world, int x, int y);
    
protected:
    void OnCollision()override;
};
