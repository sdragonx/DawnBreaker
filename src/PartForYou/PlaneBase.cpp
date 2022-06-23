#include "PlaneBase.h"
#include "GameWorld.h"
#include "Explosion.h"

//
// PlaneBase
//

PlaneBase::PlaneBase(GameWorld* world, int imageID, int x, int y, int direction, int layer, double size) :
    GameObject(world, imageID, x, y, direction, layer, size),
    m_level(1),
    m_HP(),
    m_MP(),
    m_damage(),
    m_speed()
{

}

void PlaneBase::SetLevel(int n)
{
    m_level = n;
}

int PlaneBase::GetLevel()const
{
    return m_level;
}

void PlaneBase::LevelUp()
{
    ++m_level;
}

void PlaneBase::SetHP(int n)
{
    m_HP = n;
}

int PlaneBase::GetHP()const
{
    return m_HP;
}

void PlaneBase::AddHP(int n)
{
    m_HP += n;
    if (m_HP <= 0) {
        m_HP = 0;
        this->Destroy();
    }
    //printf("HP = %d\n", m_HP);
}

void PlaneBase::SetMP(int n)
{
    m_MP = n;
}

int PlaneBase::GetMP()const
{
    return m_MP;
}

void PlaneBase::AddMP(int n)
{
    m_MP += n;
    if (m_MP <= 0) {
        m_MP = 0;
    }
}

void PlaneBase::SetSpeed(int n)
{
    m_speed = n;
}

int PlaneBase::GetSpeed()const
{
    return m_speed;
}

void PlaneBase::SetDamage(int n)
{
    m_damage = n;
}

int PlaneBase::GetDamage()const
{
    return m_damage;
}

// destroy this plane
void PlaneBase::Destroy()
{
    world()->AddObject(new Explosion(world(), GetX(), GetY()));
    this->SetMissing(true);
}
