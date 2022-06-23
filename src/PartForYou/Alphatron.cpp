#include "Alphatron.h"
#include "GameWorld.h"
#include "RedBullet.h"

//
// Alphatron
//

Alphatron::Alphatron(GameWorld* world, int x, int y, int hp, int damage, int speed) :
    EnemyBase(world, IMGID_ALPHATRON, x, y, 180, 0, 1.0)
{
    this->SetHP(hp);
    this->SetDamage(damage);
    this->SetSpeed(speed);
    this->SetMP(25);
}

void Alphatron::OnAttack()// 4.
{
    PlaneBase *plane = world()->GetDawnBreaker();
    int w = abs(this->GetX() - plane->GetX());
    if (w <= 10) {
        if (GetMP() >= 25) {
            int n = randInt(0, 100);
            if (n < 25) {
                AddMP(-25);

                // fire
                world()->AddObject(new RedBullet(this, GetX(), GetY() - 50, 180, this->GetDamage()));
            }
        }
    }

    // 5. add mp
    if (GetMP() < 25) {
        AddMP(1);
    }
}
//
//void Alphatron::NextMoveMode()// 6.
//{
//    if (GetMoveTime() < 0) {
//        int n = randInt(1, 3);
//        SetMoveMode((MoveMode)n);
//
//        n = randInt(10, 50);
//        SetMoveTime(n);
//    }
//    else if (GetX() < 0) {
//        SetMoveMode(MoveMode::RightDown);
//        SetMoveTime(randInt(10, 50));
//    }
//    else if (GetX() > WINDOW_WIDTH) {
//        SetMoveMode(MoveMode::LeftDown);
//        SetMoveTime(randInt(10, 50));
//    }
//}


void Alphatron::OnDropItem()
{
    world()->KillEnemy(50);
}
