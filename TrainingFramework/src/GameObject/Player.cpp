#include "Player.h"
#include "GameManager/ResourceManagers.h"
#include "ExplosiveEffect.h"

Player::Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_TargetPosition = Vector2(0, 0);
	m_MaxCooldown = 0.1;
	m_Cooldown = 0.0;
	m_speed = 300;
	m_MaxSpeed = 500;
	m_Heal = 100;
	m_SizeCollider = 20;
	m_isAlive = true;
}

Player::~Player()
{
}


void Player::MoveToPossition(Vector2 pos)
{
	m_TargetPosition = pos;
}



void Player::Update(GLfloat deltatime)
{
	if (!m_isAlive)
		return;

	if (m_Heal <= 0)
	{
		SoundManager::GetInstance()->PlaySound("die");
		m_isAlive = false;
		return;
	}
	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltatime;
	}

	Vector2 pos = Get2DPosition();

	if (pos.x < m_TargetPosition.x)
	{
		pos.x += m_speed * deltatime;
		if (pos.x > m_TargetPosition.x)
			pos.x = m_TargetPosition.x;
	}

	if (pos.x > m_TargetPosition.x)
	{
		pos.x -= m_speed * deltatime;
		if (pos.x < m_TargetPosition.x)
			pos.x = m_TargetPosition.x;
	}

	if (pos.y < m_TargetPosition.y)
	{
		pos.y += m_speed * deltatime;
		if (pos.y > m_TargetPosition.y)
			pos.y = m_TargetPosition.y;
	}

	if (pos.y > m_TargetPosition.y)
	{
		pos.y -= m_speed * deltatime;
		if (pos.y < m_TargetPosition.y)
			pos.y = m_TargetPosition.y;
	}

	Set2DPosition(pos);
}

bool Player::CanShoot()
{
	return (m_Cooldown <= 0);
}

void Player::Shoot(std::vector<std::shared_ptr<Bullet>>& listBullet)
{
	SoundManager::GetInstance()->PlaySound("nem");
	m_Cooldown = m_MaxCooldown;
	for (auto bullet : listBullet)
	{
		if (!bullet->IsActive())
		{
			bullet->SetActive(true);
			bullet->Set2DPosition(Get2DPosition());
			bullet->SetSpeed(150);
			bullet->SetType(BULLET_TYPE::Player);
			return;
		}
	}

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("phitieu");

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture);
	bullet->SetSize(20, 20);
	bullet->Set2DPosition(Get2DPosition());
	bullet->SetSpeed(150);
	bullet->SetType(BULLET_TYPE::Player);

	listBullet.push_back(bullet);


}
void Player::Chem(Vector2 pos) {
	SoundManager::GetInstance()->PlaySound("attack");
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("NV");
	auto shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(1070, 422), Vector2(267.5, 211), 0, 7, 0.7);
	exp->SetSize(100, 100);
	exp->Set2DPosition(pos);
	exp->Draw();


}
float Player::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}


//void Player::CheckChem(std::vector<std::shared_ptr<ExplosiveEffect>>& listexp) {
//
//}

void Player::CheckCollider(std::vector<std::shared_ptr<Bullet>>& listBullet, std::vector<std::shared_ptr<Enermy>> listEnermy)
{
	Vector2 pos = Get2DPosition();
	for (auto enermy : listEnermy)
	{
		if (enermy->IsActive())
		{
			if (distance(pos, enermy->Get2DPosition()) < m_SizeCollider + enermy->GetColliderSize())
			{
				enermy->Explosive();
				m_Heal -= enermy->GetDamage();
					//SoundManager::GetInstance()->PauseSound("joke");
					//SoundManager::GetInstance()->PauseSound("joke");
					//SoundManager::GetInstance()->AddSound("joke");
					SoundManager::GetInstance()->PlaySound("joke");
				
			}
		}
	}

	for (auto bullet : listBullet)
	{
		if (bullet->IsActive() && bullet->GetType() == BULLET_TYPE::Enermy)
		{
			if (distance(pos, bullet->Get2DPosition()) < m_SizeCollider + bullet->GetColliderSize())
			{
				bullet->SetActive(false);
				m_Heal -= bullet->GetDamage();
			
			}
		}
	}
}

void Player::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Player::GetColliderSize()
{
	return m_SizeCollider;
}

int Player::GetHeal()
{
	return m_Heal;
}

bool Player::IsAlive()
{
	return m_isAlive;
}
