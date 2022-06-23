#pragma once

#include "ItemBase.h"


class HPRestoreGoodie : public ItemBase
{
public:
    HPRestoreGoodie(GameWorld* world, int x, int y);
    
protected:
    void OnCollision()override;
};
