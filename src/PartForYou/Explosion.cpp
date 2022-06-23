#include "Explosion.h"


//
// Explosion
//

Explosion::Explosion(GameWorld* world, int x, int y) :
    GameObject(world, IMGID_EXPLOSION, x, y, 0, 3, 4.5),
    m_tick(0)
{

}

Explosion::~Explosion()
{

}

void Explosion::Update()
{
    if (this->IsMissing()) {
        return;
    }

    this->SetSize(this->GetSize() - 0.2);
    ++m_tick;
    if (m_tick >= 20) {
        this->SetMissing(true);
    }
}
