#pragma once

#include "EnemyBase.h"
#include "BulletBase.h"

// Alphatron
class Alphatron : public EnemyBase
{
public:
    Alphatron(GameWorld* world, int x, int y, int hp, int damage, int speed);

private:
    void OnAttack()override;
    void OnDropItem()override;
};
