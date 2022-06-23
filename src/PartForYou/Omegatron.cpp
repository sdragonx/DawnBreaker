#include "Omegatron.h"
#include "GameWorld.h"
#include "RedBullet.h"
#include "PowerUpGoodie.h"
#include "MeteorGoodie.h"

//
// Omegatron
//

Omegatron::Omegatron(GameWorld* world, int x, int y, int hp, int damage, int speed) :
    EnemyBase(world, IMGID_OMEGATRON, x, y, 180, 0, 1.0)
{
    this->SetHP(hp);
    this->SetMP(50);
    this->SetDamage(damage);
    this->SetSpeed(speed);
}

void Omegatron::OnAttack()// 4.
{
    PlaneBase *plane = world()->GetDawnBreaker();
    int w = abs(this->GetX() - plane->GetX());

    if (GetMP() >= 50) {
        AddMP(-50);

        // fire
        world()->AddObject(new RedBullet(this, GetX(), GetY() - 50, 162, this->GetDamage()));
        world()->AddObject(new RedBullet(this, GetX(), GetY() - 50, 198, this->GetDamage()));
    }

    // 5. add mp
    if (GetMP() < 50) {
        AddMP(1);
    }
}

void Omegatron::OnDropItem()
{
    world()->KillEnemy(200);

    // 40% 掉落道具
    int n = randInt(0, 100);
    if (n < 40) {
        n = randInt(0, 100);
        if (n < 20) {// 20% 陨石
            world()->AddObject(new MeteorGoodie(world(), GetX(), GetY()));
        }
        else {// 80% 升级道具
            world()->AddObject(new PowerUpGoodie(world(), GetX(), GetY()));
        }
    }
}
