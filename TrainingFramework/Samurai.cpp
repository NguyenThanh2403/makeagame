#include "Samurai.h"
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>


Samurai::Samurai(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_active = false;
	m_MaxCooldown = 0.5;
	m_Cooldown = 0.0;
	m_speed = 100;
	m_MaxSpeed = 500;
	m_Heal = 5;
	m_Damage = 10;
	m_Explosive = false;
	m_SizeCollider = 20;
}

Samurai::~Samurai()
{
}

void Samurai::Update(float deltaTime)
{
	if (!m_active)
		return;

	if (m_Heal <= 0 || m_Explosive)
	{
		SoundManager::GetInstance()->PlaySound("enamidie");
		m_Explosive = true;
		GSPlay::m_score++;
		return;
	}

	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltaTime;
	}

	Vector2 pos = Get2DPosition();
	pos.y = pos.y + m_speed * deltaTime;
	Set2DPosition(pos);

	if (pos.y > Application::screenWidth)
		m_active = false;
}


void Samurai::CheckCollider(std::vector<std::shared_ptr<Bullet>>& listBullet)
{
	Vector2 pos = Get2DPosition();

	for (auto bullet : listBullet)
	{
		if (bullet->IsActive() && bullet->GetType() == BULLET_TYPE::Player)
		{
			if (distance(pos, bullet->Get2DPosition()) < m_SizeCollider + bullet->GetColliderSize())
			{
				bullet->SetActive(false);
				m_Heal -= bullet->GetDamage();
				if (m_Heal <= 0)
					return;
			}
		}
	}
}

float Samurai::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}

bool Samurai::IsActive()
{
	return m_active;
}

void Samurai::SetActive(bool status)
{
	m_active = status;
	m_Explosive = false;
	m_Heal = 20;
}

void Samurai::SetDamage(float damage)
{
	m_Damage = damage;
}

float Samurai::GetDamage()
{
	return m_Damage;
}

void Samurai::Explosive()
{
	m_Explosive = true;
}

bool Samurai::IsExplosive()
{
	return m_Explosive;
}

void Samurai::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Samurai::GetColliderSize()
{
	return m_SizeCollider;
}
