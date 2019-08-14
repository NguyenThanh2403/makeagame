#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class Player;
class Bullet;
class Enermy;
class Samurai;
class Text;
class ExplosiveEffect;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init()override;
	void Exit()override;

	void Pause()override;
	void Resume()override;

	void HandleEvents() override;
	void HandleKeyEvents(int key, bool bIsPressed) override;
	void HandleMouseEvents(int x, int y) override;

	void HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void Update(float deltaTime) override;
	void Draw() override;
	
	static int m_score;
	 int Rskill = 0;


private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_ava;
	std::shared_ptr<Text>  m_scoreText;
	std::shared_ptr<Text>  m_skillText;
	std::shared_ptr<Text>  m_playerHealText;
	std::shared_ptr<Player> m_Player;
	std::vector<std::shared_ptr<Bullet>> m_listBullet;
	std::vector<std::shared_ptr<Enermy>> m_listEnermy;
	std::vector<std::shared_ptr<Samurai>> m_listSamurai;
	std::vector<std::shared_ptr<ExplosiveEffect>> m_listExplosiveEffect;
	std::vector<std::shared_ptr<ExplosiveEffect>> m_listexp;

	float m_SpawnCooldown;
	void CreateRandomEnermy();
	void CreateRandomSamurai();
	void SpawnExplosive(Vector2 pos);
	void Checkexp(Vector2 pos);

	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Texture>>	m_texture;

	
};

