#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <algorithm>
#include <list>

#include "WorldBase.h"
#include "GameObjects.h"
#include "DawnBreaker.h"

class GameWorld : public WorldBase {
public:
  GameWorld();
  virtual ~GameWorld();

  virtual void Init() override;

  virtual LevelStatus Update() override;

  virtual void CleanUp() override;

  virtual bool IsGameOver() const override;

  // get key states
  ControlKeys GetKeys();

  // add object
  void AddObject(GameObject* object);

  // get DawnBreaker
  DawnBreaker* GetDawnBreaker()const;

  // add killed + score
  void KillEnemy(int score);

  // get objects
  std::list<GameObject*> Objects()const;

private:
    std::list<GameObject*> m_objects;
    DawnBreaker* m_player;

    int m_lives;
    int m_destroyed;

    int Required()const;
    int MaxOnScreen()const;

    // total enemies
    int TotalEnemy();

    // generate enemy
    void GenEnemy();
};

#endif // !GAMEWORLD_H__
