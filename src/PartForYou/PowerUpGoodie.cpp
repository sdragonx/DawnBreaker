#include "PowerUpGoodie.h"
#include "GameWorld.h"
#include "PlaneBase.h"

PowerUpGoodie::PowerUpGoodie(GameWorld* world, int x, int y) :
    ItemBase(world, IMGID_POWERUP_GOODIE, x, y)
{

}
    
void PowerUpGoodie::OnCollision()
{
    DawnBreaker* plane = world()->GetDawnBreaker();
    plane->LevelUp();
    world()->IncreaseScore(20);
}
