#pragma once

#include "GameObjects.h"

//
// PlaneBase
//

class PlaneBase : public GameObject
{
public:
    PlaneBase(GameWorld* world, int imageID, int x, int y, int direction, int layer, double size);

    bool IsPlane()const override final { return true; }

    void SetLevel(int n);       // Level
    int GetLevel()const;
    void LevelUp();

    void SetHP(int n);          // HP
    int GetHP()const;
    void AddHP(int n);

    void SetMP(int n);          // MP
    int GetMP()const;
    void AddMP(int n);

    void SetSpeed(int n);       // speed
    int GetSpeed()const;

    void SetDamage(int n);      // damage
    int GetDamage()const;

    virtual void Destroy()override;

private:
    int m_level;
    int m_HP;
    int m_MP;
    int m_speed;
    int m_damage;
};
