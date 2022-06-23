#pragma once

#include "EnemyBase.h"
#include "BulletBase.h"

// Sigmatron
class Sigmatron : public EnemyBase
{
public:
    Sigmatron(GameWorld* world, int x, int y, int hp, int speed);

private:
    void OnAttack()override;
    void OnDropItem()override;
};
