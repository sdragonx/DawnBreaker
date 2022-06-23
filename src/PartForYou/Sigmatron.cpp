#include "Sigmatron.h"
#include "GameWorld.h"
#include "RedBullet.h"
#include "HPRestoreGoodie.h"

//
// Sigmatron
//

Sigmatron::Sigmatron(GameWorld* world, int x, int y, int hp, int speed) :
    EnemyBase(world, IMGID_SIGMATRON, x, y, 180, 0, 1.0)
{
    this->SetHP(hp);
    this->SetMP(0);
    this->SetSpeed(speed);
}

void Sigmatron::OnAttack()// 4.
{
    PlaneBase *plane = world()->GetDawnBreaker();
    int w = abs(this->GetX() - plane->GetX());
    if (w <= 10) {
        SetMoveMode(MoveMode::Down);
        SetSpeed(10);
        SetMoveTime(9999);
    }
}

void Sigmatron::OnDropItem()
{
    world()->KillEnemy(100);

    // HP item 20%
    int n = randInt(0, 100);
    if (n < 20) {
        world()->AddObject(new HPRestoreGoodie(world(), GetX(), GetY()));
    }
}
