#pragma once

#include "EnemyBase.h"

// Omegatron
class Omegatron : public EnemyBase
{
public:
    Omegatron(GameWorld* world, int x, int y, int hp, int damage, int speed);

private:
    void OnAttack()override;
    void OnDropItem()override;
};
