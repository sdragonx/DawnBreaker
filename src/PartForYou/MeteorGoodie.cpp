#include "MeteorGoodie.h"
#include "GameWorld.h"

MeteorGoodie::MeteorGoodie(GameWorld* world, int x, int y) :
    ItemBase(world, IMGID_METEOR_GOODIE, x, y)
{

}
    
void MeteorGoodie::OnCollision()
{
    DawnBreaker* plane = world()->GetDawnBreaker();

    plane->AddMeteor(1);
    world()->IncreaseScore(20);
}
