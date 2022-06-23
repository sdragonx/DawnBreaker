#pragma once

#include "PlaneBase.h"
#include "BulletBase.h"

// DawnBreaker
class DawnBreaker : public PlaneBase
{
public:
    DawnBreaker(GameWorld* world);

    // is player
    bool IsPlayer()const final override { return true; }

    void SetMeteor(int n);      // Meteor
    int GetMeteor()const;
    void AddMeteor(int n);

    void Update()override;

private:
    int m_meteor;

};
