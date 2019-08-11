#include <sstream>
#include <iomanip>
#include <thread>
#include "GSPlay.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Text.h"
#include "Player.h"
#include "Enermy.h"
#include "Bullet.h"
#include "ExplosiveEffect.h"

int GSPlay::m_score = 0;
GSPlay::GSPlay()
{

	m_SpawnCooldown = 0.5;
	m_score = 0;
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("ioniaa");
	m_texture.push_back(texture);
	texture = ResourceManagers::GetInstance()->GetTexture("ionia");
	m_texture.push_back(texture);

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);


	//player
	texture = ResourceManagers::GetInstance()->GetTexture("samurai");
	m_Player = std::make_shared<Player >(model, shader, texture);
	m_Player->Set2DPosition(Application::screenWidth / 2, Application::screenHeight - 100);
	m_Player->MoveToPossition(Vector2(Application::screenWidth / 2, Application::screenHeight - 100));
	m_Player->SetSize(75, 75);

	//resume button
	texture = ResourceManagers::GetInstance()->GetTexture("Repit");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(850, 30));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);


	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("Back");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(925, 30));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("phong");
	m_scoreText = std::make_shared< Text>(shader, font, "KILL: ", TEXT_COLOR::BLACK, 1.0);
	m_scoreText->Set2DPosition(Vector2(4, 25));
	m_playerHealText = std::make_shared< Text>(shader, font, "HP" , TEXT_COLOR::RED, 1.0);
	m_playerHealText->Set2DPosition(Vector2(5, 50));




	//init effect
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	texture = ResourceManagers::GetInstance()->GetTexture("Bom");
	shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(1070, 422), Vector2(267.5, 211), 0, 7, 0.7);
	exp->SetSize(100, 100);
	exp->SetActive(false);
	m_listExplosiveEffect.push_back(exp);
	//init sound
	SoundManager::GetInstance()->AddSound("explosive");
	SoundManager::GetInstance()->AddSound("explosive_2");
	SoundManager::GetInstance()->AddSound("yasou_play");
	SoundManager::GetInstance()->AddSound("fire");
	SoundManager::GetInstance()->AddSound("fire_enemy");
	SoundManager::GetInstance()->PlaySound("yasou_play");

}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	switch (key) {
	case 65:
		if (m_Player->CanShoot())
			m_Player->Shoot(m_listBullet);
	}
	
	
}


void GSPlay::HandleMouseEvents(int x, int y)
{
	//m_Player->MoveToPossition(Vector2(x, y));
}



void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_Player->MoveToPossition(Vector2(x, y));
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlay::Update(float deltaTime)
{

	if (m_SpawnCooldown > 0)
	{
		m_SpawnCooldown -= deltaTime;
	}
	if (m_SpawnCooldown <= 0)
	{
		CreateRandomEnermy();
		m_SpawnCooldown = 0.3;
	}

	//update player
	if (m_Player->IsAlive())
	{
		m_Player->Update(deltaTime);

		//if (m_Player->CanShoot())
			//m_Player->Shoot(m_listBullet);

		m_Player->CheckCollider(m_listBullet, m_listEnermy);
	}else
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);

	//update enermies
	for (auto enermy : m_listEnermy)
	{
		if (enermy->IsActive())
		{
			if (enermy->IsExplosive())
			{
				enermy->SetActive(false);
				SpawnExplosive(enermy->Get2DPosition());
				continue;
			}
			enermy->Update(deltaTime);
			if (enermy->CanShoot())
				enermy->Shoot(m_listBullet);
			enermy->CheckCollider(m_listBullet);
		}
	}



	//update samurai
	for (auto samurai : m_listSamurai)
	{
		if (samurai->IsActive())
		{
			if (samurai->IsExplosive())
			{
				samurai->SetActive(false);
				SpawnExplosive(samurai->Get2DPosition());
				continue;
			}
			samurai->Update(deltaTime);
			samurai->CheckCollider(m_listBullet);
		}
	}


	for (auto exp : m_listExplosiveEffect)
	{
		if (exp->IsActive())
		{
			exp->Update(deltaTime);
		}
	}

	//update bullets
	for (auto bullet : m_listBullet)
	{
		if (bullet->IsActive())
			bullet->Update(deltaTime);
	}

	//update Score
	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << m_score;
	std::string score = "KILL: " + stream.str();
	m_scoreText->setText(score);
	std::stringstream stream2;
	stream2 << std::fixed << std::setprecision(0) << m_Player->GetHeal();
	std::string heal = "HP: " + stream2.str();
	m_playerHealText->setText(heal);
	//upsate button
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	//ground
	m_BackGround->Draw();

	for (auto enermy : m_listEnermy)
		if (enermy->IsActive())
			enermy->Draw();

	for (auto samurai : m_listSamurai)
		if (samurai->IsActive())
			samurai->Draw();


	if (m_Player->IsAlive())
		m_Player->Draw();

	for (auto bullet : m_listBullet)
		if (bullet->IsActive())
			bullet->Draw();

	for (auto exp : m_listExplosiveEffect)
	{
		if (exp->IsActive())
		{
			exp->Draw();
		}
	}

	//UI
	m_scoreText->Draw();
	m_playerHealText->Draw();
	//butoon
	
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	
}

void GSPlay::CreateRandomEnermy()
{

	int range = Application::screenWidth - 10 + 1;
	int num = rand() % range + 10;

	Vector2 pos;
	pos.x = num;
	pos.y = 10;

	for (auto enermy : m_listEnermy)
	{
		if (!enermy->IsActive())
		{
			enermy->SetActive(true);
			enermy->Set2DPosition(pos);
			return;
		}
	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("enami");

	std::shared_ptr<Enermy> enermy = std::make_shared<Enermy>(model, shader, texture);
	enermy->Set2DPosition(pos);
	enermy->SetSize(50, 50);
	enermy->SetRotation(180);
	m_listEnermy.push_back(enermy);
}


void GSPlay::CreateRandomSamurai()
{

	int range = Application::screenHeight - 10 + 1;
	
	int num = rand() % range + 10;

	Vector2 pos;
	pos.y = num;
	pos.x = 10;

	for (auto samurai : m_listSamurai)
	{
		if (!samurai->IsActive())
		{
			samurai->SetActive(true);
			samurai->Set2DPosition(pos);
			return;
		}
	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("samurai");

	std::shared_ptr<Enermy> samurai = std::make_shared<Enermy>(model, shader, texture);
	samurai->Set2DPosition(pos);
	samurai->SetSize(30, 30);
	samurai->SetRotation(180);
	m_listEnermy.push_back(samurai);
}

void GSPlay::SpawnExplosive(Vector2 pos)
{
	for (auto exp : m_listExplosiveEffect)
	{
		if (!exp->IsActive())
		{
			exp->SetActive(true);
			exp->Set2DPosition(pos);
			return;
		}
	}

	//animation
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Bom");
	auto shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(1070, 422), Vector2(267.5, 211), 0, 7, 0.7);
	exp->SetSize(100, 100);
	exp->Set2DPosition(pos);
	m_listExplosiveEffect.push_back(exp);
}
