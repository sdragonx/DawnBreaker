#include "DawnBreaker.h"
#include "GameWorld.h"
#include "BlueBullet.h"
#include "Meteor.h"

//
// DawnBreaker
//

DawnBreaker::DawnBreaker(GameWorld* world) :
    PlaneBase(world, IMGID_DAWNBREAKER, 300, 100, 0, 0, 1.0)
{
    //x = 300  y = 100
    //100 hp
    //10  mp
    this->SetHP(100);
    this->SetMP(10);
    this->SetSpeed(4);
    this->SetMeteor(0);
}

void DawnBreaker::SetMeteor(int n)
{
    m_meteor = n;
}

int DawnBreaker::GetMeteor()const
{
    return m_meteor;
}

void DawnBreaker::AddMeteor(int n)
{
    m_meteor += n;
    if (m_meteor < 0) {
        m_meteor = 0;
    }
}

void DawnBreaker::Update()
{
    if (this->IsMissing()) {
        return;
    }

    ControlKeys keys = world()->GetKeys();

    int x = this->GetX();
    int y = this->GetY();
    if (keys.Left) {
        x -= GetSpeed();
    }
    else if (keys.Right) {
        x += GetSpeed();
    }

    if (keys.Up) {
        y += GetSpeed();
    }
    else if (keys.Down) {
        y -= GetSpeed();
    }

    // check range
    if (x < 0) x = 0;
    if (x > WINDOW_WIDTH - 1) x = WINDOW_WIDTH - 1;
    if (y < 50) y = 50;
    if (y > WINDOW_HEIGHT - 1) y = WINDOW_HEIGHT - 1;

    // set pos
    this->MoveTo(x, y);

    // fire1
    if (keys.Fire1) {
        if (GetMP() >= 10) {
            AddMP(-10);

            y += 50;
            int damage = 5 * 3 * GetLevel();
            double size = 0.5 + 0.1 * GetLevel();
            world()->AddObject(new BlueBullet(this, x, y, damage, size));
        }
    }
    else if (keys.Fire2) {
        //printf("fire meteor\n");
        if (GetMeteor() > 0) {
            AddMeteor(-1);

            y += 100;
            world()->AddObject(new Meteor(world(), x, y));
        }
    }

    // MP
    if (GetMP() < 10) {
        AddMP(1);
    }
}
