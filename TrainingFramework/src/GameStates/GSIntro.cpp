#include "GSIntro.h"
GSIntro::GSIntro()
{
	m_time = 0;
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("IntroBack");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);

	//


	texture = ResourceManagers::GetInstance()->GetTexture("skip");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(900, 40));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		SoundManager::GetInstance()->PauseSound("yasuo_dance");
		});
		m_listButton.push_back(button);
	//logo
	 texture = ResourceManagers::GetInstance()->GetTexture("nt");
	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition(Vector2(480,200));
	m_logo->SetSize(200, 200);
	SoundManager::GetInstance()->AddSound("yasuo_dance");
	SoundManager::GetInstance()->PlaySound("yasuo_dance");
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("phong");
	m_Text_gameName = std::make_shared< Text>(shader, font, "HASAGI", TEXT_COLOR::RED, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(Application::screenWidth / 2 - 80, 50));
}

void GSIntro::Exit()
{
	
}


void GSIntro::Pause()
{
	
}

void GSIntro::Resume()
{
	
}


void GSIntro::HandleEvents()
{
	
}

void GSIntro::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSIntro::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	//if (bIsPressed)
	//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSIntro::HandleMouseEvents(int x, int y)
{
}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 10)
	{
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		m_time = 0;
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSIntro::Draw()
{
	m_BackGround->Draw();
	m_logo->Draw();
	m_Text_gameName->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	
}
