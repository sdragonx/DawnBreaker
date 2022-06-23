#include "EnemyBase.h"
#include "GameWorld.h"
#include "Explosion.h"

EnemyBase::EnemyBase(GameWorld* world, int imageID, int x, int y, int direction, int layer, double size) :
    PlaneBase(world, imageID, x, y, direction, layer, size),
    m_move_mode(MoveMode::None),
    m_move_time()
{

}

void EnemyBase::SetMoveMode(MoveMode mode)
{
    m_move_mode = mode;
}

MoveMode EnemyBase::GetMoveMode()const
{
    return m_move_mode;
}

void EnemyBase::SetMoveTime(int n)
{
    m_move_time = n;
}

int EnemyBase::GetMoveTime()const
{
    return m_move_time;
}

// destroy this plane
void EnemyBase::Destroy()
{
    world()->AddObject(new Explosion(world(), GetX(), GetY()));
    this->SetMissing(true);
    this->OnDropItem();
}

void EnemyBase::Update()
{
    if (this->IsMissing()) {
        //printf("Omegatron is missing\n");
        return;
    }

    if (GetY() < 0) {
        this->SetMissing(true);
        return;
    }

    // collision with blue bullet or DawnBreaker
    if (this->OnEnemyCollision()) {
        return;
    }

    // attack
    this->OnAttack();

    // move
    this->OnEnemyMove();

    // collision with blue bullet or DawnBreaker again
    this->OnEnemyCollision();
}

void EnemyBase::OnAttack()
{

}

void EnemyBase::OnDropItem()
{

}



bool EnemyBase::OnEnemyCollision()//3.
{
    for (auto obj : world()->Objects()) {
        if (!obj->IsPlayer()) {
            continue;
        }

        if (obj->IsMissing()) {
            continue;
        }

        if (obj->IsPlane()) {
            PlaneBase* plane = dynamic_cast<PlaneBase*>(obj);
            if (this->CollisionWith(plane)) {//dead
                plane->AddHP(-20);
                this->Destroy();
                return true;
            }
        }
        else if (obj->IsBullet()) {
            BulletBase* bullet = dynamic_cast<BulletBase*>(obj);
            if (this->CollisionWith(bullet)) {
                bullet->SetMissing(true);
                this->AddHP(-bullet->GetDamage());
            }
        }
        else if (obj->IsMeteor()) {//dead
            if (this->CollisionWith(obj)) {
                this->Destroy();
                return true;
            }
        }
    }

    return this->IsMissing();
}

// enemy moving logic
void EnemyBase::OnEnemyMove()
{
    OnEnemyMoveMode();

    switch (GetMoveMode()) {
    case MoveMode::Down:
        this->MoveTo(GetX(), GetY() - GetSpeed());
        break;
    case MoveMode::LeftDown:
        this->MoveTo(GetX() - GetSpeed(), GetY() - GetSpeed());
        break;
    case MoveMode::RightDown:
        this->MoveTo(GetX() + GetSpeed(), GetY() - GetSpeed());
        break;
    default:
        break;
    }
    this->SetMoveTime(this->GetMoveTime() - 1);
}

void EnemyBase::OnEnemyMoveMode()//6.
{
    if (GetMoveTime() < 0) {
        int n = randInt(1, 3);
        SetMoveMode((MoveMode)n);

        n = randInt(10, 50);
        SetMoveTime(n);
    }
    else if (GetX() < 0) {
        SetMoveMode(MoveMode::RightDown);
        SetMoveTime(randInt(10, 50));
    }
    else if (GetX() > WINDOW_WIDTH) {
        SetMoveMode(MoveMode::LeftDown);
        SetMoveTime(randInt(10, 50));
    }
}