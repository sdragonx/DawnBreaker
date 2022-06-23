#pragma once

#include "PlaneBase.h"
#include "BulletBase.h"

class EnemyBase : public PlaneBase
{
public:
    EnemyBase(GameWorld* world, int imageID, int x, int y, int direction, int layer, double size);

    void Update()override;

    // destroy this plane
    void Destroy()override;

    void SetMoveMode(MoveMode mode);
    MoveMode GetMoveMode()const;

    void SetMoveTime(int n);
    int GetMoveTime()const;

protected:
    virtual void OnAttack();
    virtual void OnDropItem();

    bool OnEnemyCollision();
    void OnEnemyMove();
    void OnEnemyMoveMode();

private:
    MoveMode m_move_mode;
    int m_move_time;
};
