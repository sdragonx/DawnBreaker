#include "GameWorld.h"

#include "Star.h"
#include "DawnBreaker.h"
#include "Alphatron.h"
#include "Omegatron.h"
#include "Sigmatron.h"

//#define WORLD_DEBUG
//#ifdef WORLD_DEBUG
//#include "../ProvidedFramework/GameManager.h"
//#define printf GameManager::Instance().printf
//#endif

using namespace std;

GameWorld::GameWorld()
{
    //this->SetLevel(1);
    m_lives = 3;
    m_destroyed = 0;
}

GameWorld::~GameWorld()
{

}

void GameWorld::Init()
{
    //printf("level %d init\n", GetLevel());

    int x, y;
    double size;

    // player
    m_player = new DawnBreaker(this);
    AddObject(m_player);

    // 30 stars
    for (int i = 0; i < 30; ++i) {
        x = randInt(0, WINDOW_WIDTH - 1);
        y = randInt(0, WINDOW_HEIGHT - 1);
        size = randInt(10, 40) * 0.01;
        AddObject(new Star(this, x, y, size));
    }
}

LevelStatus GameWorld::Update()
{

    // add star, random: 1/30
    if (randInt(0, 30) == 0) {
        int x = randInt(0, WINDOW_WIDTH - 1);
        int y = WINDOW_HEIGHT - 1;
        double size = randInt(10, 40) * 0.01;
        //size = 1.0;
        AddObject(new Star(this, x, y, size));
    }

    // generate enemy
    GenEnemy();

    // update all objects
    for (auto& obj : m_objects) {
        if (obj->IsMissing()) {
            continue;
        }
        obj->Update();
    }

    // update status
    int hp = m_player->GetHP();
    int meteors = m_player->GetMeteor();

    // check Lost
    if (hp <= 0 || m_player->IsMissing()) {// death
        m_lives--;
        return LevelStatus::DAWNBREAKER_DESTROYED;
    }
    
    // check Won
    if (m_destroyed >= this->Required()) {// clear level
        return LevelStatus::LEVEL_CLEARED;
    }

    // check missing objects
    for (auto itr = m_objects.begin(); itr != m_objects.end(); ) {
        if ((*itr)->IsMissing()) {
            delete (*itr);
            itr = m_objects.erase(itr);
        }
        else {
            ++itr;
        }
    }

    //printf("objects: %d\n", m_objects.size());

    //HP: X/100   Meteors: X   Lives: X   Level: X   Enemies: X/X   Score: X
    char buf[256] = { 0 };
    snprintf(buf, sizeof(buf), "HP: %d/100   Meteors: %d   Lives: %d   Level: %d   Enemies: %d/%d   Score: %d",
        hp, meteors, m_lives, GetLevel(), m_destroyed, Required(), GetScore());
    this->SetStatusBarMessage(buf);

    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
// clear all objects
    for (auto& obj : m_objects) {
        delete obj;
        obj = nullptr;
    }
    m_objects.clear();

    m_player = nullptr;
    m_destroyed = 0;
}


bool GameWorld::IsGameOver() const
{
//return false;
    return m_lives <= 0;
}

// get key states
ControlKeys GameWorld::GetKeys()
{
    ControlKeys keys;

    keys.Left = this->GetKey(KeyCode::LEFT);
    keys.Right = this->GetKey(KeyCode::RIGHT);
    keys.Up = this->GetKey(KeyCode::UP);
    keys.Down = this->GetKey(KeyCode::DOWN);
    keys.Fire1 = this->GetKey(KeyCode::FIRE1);
    keys.Fire2 = this->GetKeyDown(KeyCode::FIRE2);

    //printf("keys: %d %d\n", keys.Fire1, keys.Fire2);

    return keys;
}

// add object
void GameWorld::AddObject(GameObject* object)
{
    m_objects.push_back(object);
}

// get DawnBreaker
DawnBreaker* GameWorld::GetDawnBreaker()const
{
    return m_player;
}

// add score
void GameWorld::KillEnemy(int score)
{
    m_destroyed++;
    IncreaseScore(score);
}

// get objects
std::list<GameObject*> GameWorld::Objects()const
{
    return m_objects;
}

// total enemies
int GameWorld::TotalEnemy()
{
    int enemiesCount = 0;
    for (auto& obj : m_objects) {
        if (obj->IsMissing()) {
            continue;
        }

        if (obj->IsPlane() && !obj->IsPlayer()) {
            ++enemiesCount;
        }
    }
    return enemiesCount;
}

// 过关所需击毁的敌机数量为
int GameWorld::Required()const
{
    return 3 * GetLevel();
}

// 关卡允许屏幕上最多存在的敌机数量为 
int GameWorld::MaxOnScreen()const
{
    return (5 + GetLevel()) / 2;
}

// generate enemy
void GameWorld::GenEnemy()
{
    //2.
    int level = this->GetLevel();
    int maxOnScreen = MaxOnScreen();

    int n = TotalEnemy();
    if (n >= maxOnScreen) {
        return;
    }

    int toDestroy = Required() - m_destroyed;       // 则还需击毁的敌机数量为
    int allowed = std::min(toDestroy, maxOnScreen); // 考虑过关条件的最多允许敌机数量为

    //printf("%d  %d\n", allowed, maxOnScreen);
    //allowed *= 10;
    n = randInt(0, 100);
    if (n >= allowed) {
        return;
    }

    //3.
    int P1 = 6;
    int P2 = 2 * std::max(level - 1, 0);
    int P3 = 3 * std::max(level - 2, 0);

    PlaneBase* plane = nullptr;
    int hp, damage, speed;

    int x = randInt(0, WINDOW_WIDTH - 1);
    int y = WINDOW_HEIGHT - 1;

    //P1 / (P1 + P2 + P3)
    n = randInt(0, P1 + P2 + P3);
    if (n < P1) {// Alphatron
        hp = 20 + 2 * level;
        damage = 4 + level;
        speed = 2 + level / 5;

        plane = new Alphatron(this, x, y, hp, damage, speed);
    }
    else if ((n - P1) < P2) {// Sigmatron
        hp = 25 + 5 * level;
        damage = 0;
        speed = 2 + level / 5;
        plane = new Sigmatron(this, x, y, hp, speed);
    }
    else {// Omegatron
        hp = 20 + level;
        damage = 2 + 2 * level;
        speed = 3 + level / 4;
        plane = new Omegatron(this, x, y, hp, damage, speed);
    }

    if (plane) {
        this->AddObject(plane);
    }
}