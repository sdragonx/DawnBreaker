#include "HPRestoreGoodie.h"
#include "GameWorld.h"

HPRestoreGoodie::HPRestoreGoodie(GameWorld* world, int x, int y) :
    ItemBase(world, IMGID_HP_RESTORE_GOODIE, x, y)
{

}
    
void HPRestoreGoodie::OnCollision()
{
    DawnBreaker* plane = world()->GetDawnBreaker();

    int hp = plane->GetHP();
    hp += 50;
    if (hp > 100) {
        hp = 100;
    }
    plane->SetHP(hp);
    world()->IncreaseScore(20);
}
