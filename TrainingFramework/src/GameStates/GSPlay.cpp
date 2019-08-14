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
#include "../../Samurai.h"
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
	//ava
	texture = ResourceManagers::GetInstance()->GetTexture("ava");
	m_ava = std::make_shared<Sprite2D>(model, shader, texture);
	m_ava->Set2DPosition(Vector2(30, 30));
	m_ava->SetSize(50, 50);

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

	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("Button_q");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(925, 140));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("Button_w");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(925, 200));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("Button_e");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(925, 260));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("Button_r");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(925, 320));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("phong");
	m_scoreText = std::make_shared< Text>(shader, font, "KILL: ", TEXT_COLOR::BLACK, 1.0);
	m_scoreText->Set2DPosition(Vector2(70, 25));
	m_playerHealText = std::make_shared< Text>(shader, font, "HP" , TEXT_COLOR::RED, 1.0);
	m_playerHealText->Set2DPosition(Vector2(70, 50));
	m_skillText = std::make_shared< Text>(shader, font, "SKILL", TEXT_COLOR::RED, 0.5);
	m_skillText->Set2DPosition(Vector2(900, 100));




	//init effect
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	texture = ResourceManagers::GetInstance()->GetTexture("Bom");
	shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(1070, 422), Vector2(267.5, 211), 0, 7, 0.7);
	exp->SetSize(100, 100);
	exp->SetActive(false);
	m_listExplosiveEffect.push_back(exp);
	
	texture = ResourceManagers::GetInstance()->GetTexture("NV");
	exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(588, 1627), Vector2(98, 140), 0, 12, 0.7);
	exp->SetSize(100, 100);
	exp->SetActive(false);
	m_listexp.push_back(exp);
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
	if (bIsPressed) {
		
		switch (key) {
		case 87:
			if (m_Player->CanShoot())
				m_Player->Shoot(m_listBullet);
			break;
		case  69:
			if (bIsPressed)
			SoundManager::GetInstance()->AddSound("cuoi");
			SoundManager::GetInstance()->PlaySound("cuoi");
			if(m_Player->GetHeal()<50)
			CreateRandomSamurai();
			break;

		case 81:
			Checkexp(m_Player->Get2DPosition());
			for (auto exp : m_listexp)
			{
				if (exp->IsActive())
				{
					exp->Draw();
				}
				//exp->SetActive(false);
			}
			m_Player->Chem(m_Player->Get2DPosition());
			break;
		case 82:
			if (bIsPressed) {
				if (Rskill > 0) {
					for (auto enermy : m_listEnermy)
					{
						if (enermy->IsActive())
						{
							enermy->SetActive(false);
							SpawnExplosive(enermy->Get2DPosition());
							continue;

							enermy->CheckCollider(m_listBullet);
						}
					}
					std::stringstream stream;
					stream << std::fixed << std::setprecision(0) << m_score;
					std::string score = "KILL: " + stream.str();
					m_scoreText->setText(score);
					m_scoreText->Draw();
					SoundManager::GetInstance()->AddSound("until");
					SoundManager::GetInstance()->PlaySound("until");
					Rskill = Rskill - 1;
					GSPlay::Update(0.01);
				}

			}
			break;
		}

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
		//CreateRandomSamurai();
		m_SpawnCooldown = 0.3;
	}

	//update player
	if (m_Player->IsAlive())
	{
		m_Player->Update(deltaTime);

		//if (m_Player->CanShoot())
			//m_Player->Shoot(m_listBullet);

		m_Player->CheckCollider(m_listBullet, m_listEnermy);
	}
	else {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Gameover);
		GSPlay::Pause();
	}

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
				samurai->SetActive(true);
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

	for (auto exp : m_listexp)
	{
		if (exp->IsActive())
		{
			exp->Update(deltaTime);
		}
	}
	//R
	if (m_score != 0 && m_score % 20 == 0) Rskill++;
	else Rskill = Rskill;

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
	m_ava->Draw();
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
	for (auto exp : m_listexp)
	{
		if (exp->IsActive())
		{
			exp->Draw();
		}
	}

	//UI
	m_scoreText->Draw();
	m_playerHealText->Draw();
	m_skillText->Draw();
	//butoon
	
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	
}

void GSPlay::CreateRandomEnermy()
{

	int range = Application::screenHeight - 150 + 1;
	int num =80+ rand()%300;//rand() % range + 10;

	Vector2 pos;
	pos.y =num;
	pos.x = 20;

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
	enermy->SetRotation(0);
	m_listEnermy.push_back(enermy);
}


void GSPlay::CreateRandomSamurai()
{

	int range = Application::screenWidth - 10 + 1;
	
	int num = rand() % 500 + 100;

	Vector2 pos;
	pos.x = m_Player->Get2DPosition().x;
	pos.y = 10;

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

	std::shared_ptr<Samurai> samurai = std::make_shared<Samurai>(model, shader, texture);
	samurai->Set2DPosition(pos);
	samurai->SetSize(40, 40);
	samurai->SetRotation(180);
	m_listSamurai.push_back(samurai);
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
	texture = ResourceManagers::GetInstance()->GetTexture("explosive");
	 exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(1070, 422), Vector2(267.5, 211), 0, 7, 0.7);
	exp->SetSize(100, 100);
	exp->Set2DPosition(pos);
	m_listExplosiveEffect.push_back(exp);
}

void GSPlay::Checkexp(Vector2 pos)
{
	for (auto exp : m_listexp)
	{
		if (!exp->IsActive())
		{
			exp->SetActive(true);
			exp->Set2DPosition(pos);
			return;
		}
	}
}
