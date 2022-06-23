#pragma once

#include "GameObjects.h"

class ItemBase : public GameObject
{
public:
    ItemBase(GameWorld* world, int imageID, int x, int y);

    bool IsItem()const final override { return true; }

    void Update()override;

protected:
    virtual void OnCollision() {}

private:
    bool Collision();
};

